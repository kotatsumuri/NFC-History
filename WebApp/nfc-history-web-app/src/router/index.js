import Vue from 'vue'
import store from '../store'
import firebase from 'firebase'
import VueRouter from 'vue-router'
import Welcome from '../views/Welcome.vue'
import Home from '../views/Home.vue'
import Setting from '../views/Setting.vue'

Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    name: 'Welcome',
    component: Welcome
  },
  {
    path: '/home',
    name: 'Home',
    component: Home
  },
  {
    path: '/setting',
    name: 'Setting',
    component: Setting
  }
]

let router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

router.beforeResolve((to, from, next) => {
  if (to.path == '/') {
    store.commit('setHeaderBtnFlag', false);
    next()
  } else {
    firebase.auth().onAuthStateChanged(user => {
      if (user) {
        store.commit('setHeaderBtnFlag', true);
        next()
      } else {
        store.commit('setHeaderBtnFlag', false);
        next({path: '/'})
      }
    })
  }
})

export default router