<template>
    <div class = "infoCard">
            <v-card
             class = "card"
             max-width = "400"
             raised
            >
                <div class = "d-flex flex-no-wrap justify-space-between">
                    <v-card class = "icon" :class = "color" :elevation = "3">
                        <v-avatar
                        class = "ma-7"
                        size = "20"
                        tile>
                            <v-icon dark size = "50">{{icon}}</v-icon>
                        </v-avatar>
                    </v-card>
                    <div>
                        <v-card-text class = "text-right">
                            {{title}}
                            <div class = "headline">
                                {{value + ' ' + unit}}
                            </div>
                        </v-card-text>
                    </div>
                </div>
            </v-card>
    </div>
</template>

<script>
export default {
    name: 'InfoCard',

    props: {
        title: {
            type: String,
            default: '残額'
        },
        value: {
            type: Number,
            default: 142
        },
        date: {
            type: String,
            default: '2020 / 1 / 1'
        },
        color: {
            type: String,
            default: 'yellow'
        },
        icon: {
            type: String,
            default: 'mdi-cash-usd-outline'
        },
        unit: {
            type: String,
            default: '円'
        }
    }
}
</script>

<style scoped>
.card {
    margin: auto;
}
.icon {
    margin:5px;
}
</style>