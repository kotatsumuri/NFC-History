<template>
    <div class = "pageHeader">
        <v-app-bar fixed app>
            <v-toolbar-title @click = "pageRedirectForWelcome">NFC-History</v-toolbar-title>
            <div class = "flex-grow-1"></div>
            <v-toolbar-items v-show = "$store.getters.headerBtnFlag">
                <v-btn
                 text
                 v-for = "toolbarItem in toolbarItems"
                 :key = "toolbarItem.id"
                 @click = "pageRedirect(toolbarItem.url)"
                >
                {{toolbarItem.name}}
                </v-btn>
                <v-btn
                 text
                 @click = "pageRedirectForWelcome"
                >
                    ログアウト
                </v-btn>
            </v-toolbar-items>
        </v-app-bar>
    </div>
</template>

<script>
import firebase from 'firebase';

export default {
    name: 'PageHeader',

    data: function() {
        return {
            toolbarItems: [
                {id: 0, name: 'Home', url: '/home'},
                {id: 1, name: '設定', url: '/setting'}
            ]
        }
    },

    methods: {
        pageRedirect: function(url) {
            this.$router.push(url);
        },
        logout: function() {
            const _this = this;
            firebase.auth().signOut().then(function() {
                _this.pageRedirect('/');
            }).catch(function(error) {
                alert(error.message);
            });
        },
        pageRedirectForWelcome: function() {
            this.logout();
        },
    },
}
</script>