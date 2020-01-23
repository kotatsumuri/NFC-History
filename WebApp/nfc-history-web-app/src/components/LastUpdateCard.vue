<template>
    <div class = "lastUpdateCard">
        <v-card>
            <v-card-text>
                <div class = "d-flex flex-no-wrap justify-space-between">
                    <div class = "text-left">
                    最終更新
                    </div>
                    <div class = "text-right">
                    {{date}}
                    </div>
                </div>
             </v-card-text>
        </v-card>
    </div>
</template>

<script>
export default {
    name: 'LastUpdateCard',
    
    props: {
        date: {
            type: String,
            default: "2020/1/1 10:30"
        }
    }
    
}
</script>