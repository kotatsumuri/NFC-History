import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
	state: {
		headerBtnFlag: true,
		userData: {},
		user: {
			name: '',
			email: '',
			uid: ''
		}
	},
	mutations: {
		setHeaderBtnFlag: function(state, value) {
			state.headerBtnFlag = value;
		},
		
		setUserData: function(state, dataBaseValue) {
			state.userData = dataBaseValue;
		},

		setUserInfo: function(state, _user) {
			state.user.email = _user.email;
			state.user.name = _user.name;
			state.user.uid = _user.uid;
		}
	},
	getters: {
		headerBtnFlag: function(state) {
			return state.headerBtnFlag;
		},

		userData: function(state) {
			return state.userData;
		},

		user: function(state) {
			return state.user;
		},
	},
	actions: {
	},
	modules: {
	}
})
