<template>
    <div class = "setting">
        <v-container>
            <v-layout wrap>
                <v-flex xs12>
                    <device-setting>
                    </device-setting>
                </v-flex>
            </v-layout>
        </v-container>
    </div>
</template>

<script>
import DeviceSetting from '../components/DeviceSetting'

export default {
    name: 'Setting',

    components: {
        DeviceSetting
    }
}
</script>