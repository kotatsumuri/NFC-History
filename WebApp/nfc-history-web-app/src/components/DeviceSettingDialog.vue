<template>
    <div class = "deviceSettingDialog">
        <v-dialog
         v-model = "dialog"
         width = 500
        >
            <template v-slot:activator = "{ on }">
                <v-btn
                 color = "primary"
                 v-on = "on"
                >
                設定
                </v-btn>
            </template>
            <v-card>
                <v-card-text class = "pt-4">
                    <ol>
                        <li>読み取りデバイスの電源を入れてください</li>
                        <li>
                            以下のWi-Fiアクセスポイントに接続してください
                            <ul>
                                <li>SSID : nfchistory</li>
                                <li>PassWord : 415411 </li>
                            </ul>
                        </li>
                        <li>
                            <a href = "http://192.168.4.1">http://192.168.4.1</a>にアクセスし，接続したいWi-FiのSSIDとパスワード,登録したメールアドレスを入力してください
                        </li>
                    </ol>
                </v-card-text>
            </v-card>
        </v-dialog>
    </div>
</template>

<script>
export default {
    name: 'DeviceSettingDialog',

    data: function() {
        return {
            dialog: false
        }
    }
}
</script>

<style scoped>

</style>