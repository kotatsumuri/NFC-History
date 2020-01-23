import time
import datetime
import csv
import copy
import threading
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
from firebase_admin import auth
import requests
from bs4 import BeautifulSoup
import re


class Firebase:
    def __init__(self):
        self.JST = datetime.timezone(datetime.timedelta(hours =+ 9), 'JST')
        self.TERMINAL = {  3 : '精算機',
                           4 : '携帯端末',
                           5 : '車載端末',
                           7 : '券売機',
                           8 : '券売機',
                           9 : '入金機',
                          18 : '券売機',
                          20 : '券売機等',
                          21 : '券売機等',
                          22 : '改札機',
                          23 : '簡易改札機',
                          24 : '窓口端末',
                          25 : '窓口端末',
                          26 : '改札端末',
                          27 : '携帯電話',
                          28 : '乗継精算機',
                          29 : '連絡改札機',
                          31 : '簡易入金機',
                          70 : 'VIEW ALTTE',
                          72 : 'VIEW ALTTE',
                         199 : '物販端末',
                         200 : '自販機'}
        self.parseCSV()
        self.cred = credentials.Certificate('./nfc-history-firebase-adminsdk.json')
        firebase_admin.initialize_app(self.cred, {
            'databaseURL' : 'https://nfc-history.firebaseio.com/'
        })
        
        self.usersRef = db.reference('users/')
        self.getUsersData()
        if not isinstance(self.usersData, dict):
            self.usersData = {}
        
        self.devicesRef = db.reference('devices')
        self.getDevicesData()
        if not isinstance(self.devicesData, dict):
            self.devicesData = {}
        
    def __del__(self):
        self.updateDB()
    
    def __threadInit(self):
        self.thread = threading.Thread(target = self.__run)
        self.thread.daemon = True
        self.thread.start()
    
    def __run(self):
        thread = threading.Timer(10, __run)
        thread.start()
        
        self.refreshDB()
    
    def parseCSV(self):
        file = open('./StationCode.csv', 'r')
        
        dataReader = csv.reader(file)
        self.stationInfo = {}
        array = []
        ar = []
        header = next(dataReader)
        
        for row in dataReader:
            if not row[0] in array:
                array.append(row[0])
                self.stationInfo[int(row[0])] = {}
                ar = []
            if not row[1] in ar:
                ar.append(row[1])
                self.stationInfo[int(row[0])][int(row[1])] = {}
            self.stationInfo[int(row[0])][int(row[1])][int(row[2])] = {
                'CompanyName' : row[3],
                'LineName' : row[4],
                'StationName' : row[5]
            }
        
        file.close()
    
    def updateDB(self):
        self.usersRef.update(self.usersData)
        self.devicesRef.update(self.devicesData)
    
    def refreshDB(self):
        #self.updateDB()
        self.getUsersData()
        self.getDevicesData()
        
    def getUsersData(self):
        self.usersData = copy.deepcopy(self.usersRef.get())
    
    def getDevicesData(self):
        self.devicesData = copy.deepcopy(self.devicesRef.get())
    
    def setChipID(self, chipID, email):
        self.refreshDB()
        if not chipID in self.devicesData:
            user = auth.get_user_by_email(email)
            print(user.uid)
            self.devicesData[chipID] = user.uid
            self.updateDB()
        
    def updateBalance(self, chipID, idm, balance):
        self.refreshDB()
        uid = self.devicesData[chipID]
        
        if not uid in self.usersData:
            self.usersData[uid] = {}
        if not 'card_info' in self.usersData[uid]:
            self.usersData[uid]['card_info'] = {}
        if not idm in self.usersData[uid]['card_info']:
            self.usersData[uid]['card_info'][idm] = {}
            if not 'card_list' in self.usersData[uid]:
                self.usersData[uid]['cars_list'] = []
            self.usersData[uid]['card_list'].append(idm)
        if not 'info' in self.usersData[uid]['card_info'][idm]:
            self.usersData[uid]['card_info'][idm]['info'] = {
                'balance' : 0,
                'lastUpdate' : 0,
                'read' : 0,
                'rides' : 0,
                'usage' : 0
            }
        self.usersData[uid]['card_info'][idm]['info']['balance'] = balance
        self.usersData[uid]['card_info'][idm]['info']['lastUpdate'] = datetime.datetime.fromtimestamp(time.time(), self.JST).strftime("%Y/%m/%d %H:%M:%S")
        self.usersData[uid]['card_info'][idm]['info']['read'] += 1
        self.updateDB()
    
    def updateHistory(self, chipID, idm, history):
        self.refreshDB()
        uid = self.devicesData[chipID]
        
        if not 'history_arry' in self.usersData[uid]['card_info'][idm]:
            self.usersData[uid]['card_info'][idm]['history_arry'] = []
        
        if not str(history) in self.usersData[uid]['card_info'][idm]['history_arry']:
            cp_history = history
            history_list = []
            
            for i in range(16):
                history_list.append(cp_history % 0x100)
                cp_history = cp_history >> 8
                print('{:X}'.format(history_list[i]))
                
            if history_list[14] == 1:
                self.usersData[uid]['card_info'][idm]['history_arry'].append(str(history))
                terminal = self.TERMINAL[history_list[15]]
                process = '運賃支払'
                
                year = (history_list[11] >> 1) + 2000
                month = ((history_list[11] & 1) << 3) | (history_list[10] >> 5)
                day = history_list[10] & 0b11111
                
                date = str(year) + '/' + str(month) + '/' + str(day)
                enterRegion = history_list[0] >> 6
                print(history_list[0])
                enter = self.stationInfo[enterRegion][history_list[9]][history_list[8]]['StationName']
                exitRegion = (history_list[0] >> 4) & 0b11
                exit_ = self.stationInfo[exitRegion][history_list[7]][history_list[6]]['StationName']
                usage = self.scripeUsage(enter, exit_)
                self.usersData[uid]['card_info'][idm]['info']['usage'] += usage
                self.usersData[uid]['card_info'][idm]['info']['rides'] += 1
                print(enter, exit_, usage)
                #print(date, enterRegion, exitRegion, history_list[9], history_list[8], history_list[7], history_list[6])
                if usage != -1:
                    historyInfo = {
                        'terminal' : terminal,
                        'process' : process,
                        'date' : date,
                        'enter' : enter,
                        'exit' : exit_,
                        'usage' : usage
                    }
                    if not 'history_info' in self.usersData[uid]['card_info'][idm]:
                        self.usersData[uid]['card_info'][idm]['history_info'] = []
                    self.usersData[uid]['card_info'][idm]['history_info'].insert(0, historyInfo)
                    self.updateDB()
    
    def scripeUsage(self, from_, to):
        targetUrl = "https://transit.yahoo.co.jp/search/result?from=" + from_ + "&to=" + to + "&type=5&ticket=ic&s=1"
        r = requests.get(targetUrl)
        if not r.ok:
            return -1
        soup = BeautifulSoup(r.text, 'html.parser')
        raw = soup.find(class_='fare').find(class_='mark').get_text()
        return int(re.findall('[0-9 | ,]+', raw)[0].replace(',', ''))
    
    def test(self, chipID, idm, history):
        self.testData[history] = {
            'chipID' : chipID,
            'idm' : idm
        }
        self.testRef.update(self.testData)

if __name__ == '__main__':
    firebase = Firebase()
    #firebase.updateBalance('111111', 999, str(1145141919810000))
    firebase.updateHistory('111111', str(1145141919810000), 0x160100022754A556A5AC8E0000010450)
    del firebase