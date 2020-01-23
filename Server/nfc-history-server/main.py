from flask import Flask, request
import firebase
import os

app = Flask(__name__)

fb = firebase.Firebase()
'''
@app.route('/')
def index():
    return Markup('')
'''
@app.route('/', methods = ['GET'])
def getInformation():
    if request.method == 'GET':
        chipID = request.args.get('chipID')
        dataID = int(request.args.get('dataID'))
        
        if dataID == 0:
            idm = request.args.get('idm')
            balance = int(request.args.get('balance'))
            fb.updateBalance(chipID, idm, balance)
        elif dataID == 1:
            idm = request.args.get('idm')
            history = int(request.args.get('history'), 16)
            fb.updateHistory(chipID, idm, history)
        elif dataID == 2:
            email = request.args.get('email')
            fb.setChipID(chipID, email)
            print(email)
        
        return ""

if __name__ == '__main__':
    app.debug = True
    port = int(os.getenv("PORT"))
    #port = 8080
    app.run(host = '0.0.0.0', port = port)