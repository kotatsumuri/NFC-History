<template>
    <div class = "historyCard">
        <v-card
         class = "card"
         max-width = "400"
         raised
        >
            <v-card-text>
                <div>
                    {{date}}
                </div>
                <div>
                    {{process}}
                </div>
                <div class = "headline mb-2">
                    {{usage + ' 円'}}
                </div>
                <v-divider/>
                <div class = "d-flex flex-no-wrap justify-space-between ma-4 mb-0">
                    <div class = "text-left headline name">
                        {{enter}}
                    </div>
                    <div class = "text-center headline">
                        &rarr;
                    </div>
                    <div class = "text-right headline name">
                        {{exit}}
                    </div>
                </div>
            </v-card-text>
        </v-card>
    </div>
</template>

<script>
export default {
    name: 'HistoryCard',

    props: {
        date: {
            type: String,
            default: "2020/1/1"
        },
        enter: {
            type: String,
            default: "垂井"
        },
        exit: {
            type: String,
            default: "大垣"
        },
        process: {
            type: String,
            default: "運賃支払"
        },
        usage: {
            type: Number,
            default: 1000
        }
    }
}
</script>

<style scoped>
.card {
    margin: auto
}
.name {
    width: 150px
}
</style>