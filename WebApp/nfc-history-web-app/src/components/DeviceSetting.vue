<template>
    <div class = "deviecSetting">
        <v-card
         class = "card"
         max-width = "400"
         raised
        >
            <v-card-text class = "pb-0">
                <p class = "headline text--primary">デバイスを追加</p>
                <p>Felica読み取りデバイスを追加します</p>
            </v-card-text>
            <v-divider/>
            <v-card-actions>
                <div class="flex-grow-1"></div>
                <device-setting-dialog>
                </device-setting-dialog>
            </v-card-actions>
        </v-card>
    </div>
</template>

<script>
import DeviceSettingDialog from './DeviceSettingDialog'
export default {
    name: 'DeviceSetting',

    components: {
        DeviceSettingDialog
    }
}
</script>

<style scoped>
.card {
    margin: auto
}
</style>