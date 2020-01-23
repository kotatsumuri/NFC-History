<template>
    <span class = "login">
        <v-dialog
         v-model = "dialog"
         width = "500"
        >
            <template v-slot:activator = "{ on }">
                <v-btn
                 color = "success"
                 v-on = "on"
                >
                ログイン
                </v-btn>
            </template>
            <v-card>
                <v-card-title
                >
                ログイン
                </v-card-title>
                <v-card-text>
                    <v-text-field
                    :rules = "emailRules"
                    label = "E-mail"
                    v-model = "email"
                    >
                    </v-text-field>
                    <v-text-field
                    label = "Password"
                    v-model = "password"
                    :append-icon = "showPassword ? 'mdi-eye' : 'mdi-eye-off'"
                    :type = "showPassword ? 'text' : 'password'"
                    @click:append = "showPassword = !showPassword"
                    >
                    </v-text-field>
                    <div>{{errorMessage}}</div>
                </v-card-text>
                <v-divider></v-divider>
                <v-card-actions>
                    <v-spacer/>
                    <v-btn
                     class = "ma-2"
                     color = "primary"
                     @click = "login "
                    >
                    ログイン
                    </v-btn>
                    <v-btn
                     class = "ma-2"
                     color = "error"
                     @click = "dialog = false"
                    >
                    キャンセル
                    </v-btn>
                </v-card-actions>
            </v-card>
        </v-dialog>
    </span>
</template>

<script>
import firebase from 'firebase';
export default {
    name: 'Login',

    data: function() {
        return {
            dialog: false,
            showPassword: false,
            email: '',
            password: '',
            errorMessage: '',
            emailRules: [
                v => !!v || 'E-mail is required',
                v => /.+@.+/.test(v) || 'E-mail must be valid',
            ],
        }
    },

    methods: {
        login: function() {
            const _this = this;
            firebase.auth().signInWithEmailAndPassword(this.email, this.password).then(
                result => {
                    result;
                    this.$store.commit('setUserInfo', firebase.auth().currentUser);
                    try {
                        firebase.database().ref('users/' + this.$store.getters.user.uid + '/').on('value', snapshot => {
                            this.$store.commit('setUserData', snapshot.val());
                        });
                    }
                    catch(e) {
                        /* eslint-disable */
                        console.error(e);
                    }
                    
                    this.$router.push('/home');
                    _this.dialog = false;
                }
            )
            .catch(function(error) {
                _this.errorMessage = error.message;
            });
        }
    }
}
</script>