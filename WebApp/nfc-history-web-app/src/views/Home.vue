<template>
  <div class="home">
    <v-container>
      <v-layout wrap v-if="isShow">
        <v-flex xs12>
          <v-flex xs10 sm6 md4 class="select">
            <v-select solo :items="$store.getters.userData.card_list" v-model="selectedCardID"></v-select>
          </v-flex>
        </v-flex>
        <v-flex xs12 class="ma-4 mt-0">
          <v-flex xs10 sm6 md4 class="select">
            <last-update-card :date="cardInfo.info.lastUpdate"></last-update-card>
          </v-flex>
        </v-flex>
        <v-flex xs12 v-for="infoCardElem in infoCardElems" :key="infoCardElem.key">
          <info-card
            class="card"
            :title="infoCardElem.title"
            :color="infoCardElem.color"
            :icon="infoCardElem.icon"
            :unit="infoCardElem.unit"
            :value="getValue(infoCardElem.value)"
          ></info-card>
        </v-flex>
        <v-flex xs12 v-for="(history, index) in reverseHistory" :key="index">
          <history-card
            class="card"
            :date="history.date"
            :enter="history.enter"
            :exit="history.exit"
            :process="history.process"
            :usage="history.usage"
          ></history-card>
        </v-flex>
      </v-layout>
      <v-layout v-if="!isShow">
        <v-flex>
          <div class="text-center headline resist">カードを登録してください</div>
        </v-flex>
      </v-layout>
    </v-container>
  </div>
</template>

<script>
import firebase from "firebase";
import InfoCard from "../components/InfoCard";
import HistoryCard from "../components/HistoryCard";
import LastUpdateCard from "../components/LastUpdateCard";
export default {
  name: "Home",

  components: {
    InfoCard,
    HistoryCard,
    LastUpdateCard
  },

  data: function() {
    return {
      infoCardElems: [
        {
          key: 0,
          title: "残額",
          color: "yellow darken-3",
          icon: "mdi-cash-usd-outline",
          unit: "円",
          value: "balance"
        },
        {
          key: 1,
          title: "使用金額",
          color: "green darken-1",
          icon: "mdi-cash-multiple",
          unit: "円",
          value: "usage"
        },
        {
          key: 2,
          title: "乗車回数",
          color: "cyan darken-1",
          icon: "mdi-train",
          unit: "回",
          value: "rides"
        },
        {
          key: 3,
          title: "読み取り回数",
          color: "pink darken-1",
          icon: "mdi-credit-card-wireless-outline",
          unit: "回",
          value: "read"
        }
      ],
      selectedCardID: ""
    };
  },

  created: function() {
    this.$store.commit("setUserInfo", firebase.auth().currentUser);
    try {
      firebase
        .database()
        .ref("users/" + this.$store.getters.user.uid + "/")
        .on("value", snapshot => {
          this.$store.commit("setUserData", snapshot.val());
          this.selectedCardID = this.$store.getters.userData.card_list[0];
        });
    } catch (e) {
      /* eslint-disable */
      console.error(e);
    }
  },

  computed: {
    reverseHistory: function() {
      return this.$store.getters.userData.card_info[
        this.selectedCardID
      ].history_info
        .slice()
        .reverse();
    },
    cardInfo: function() {
      return this.$store.getters.userData.card_info[this.selectedCardID];
    },
    isShow: function() {
      return this.$store.getters.userData != null;
    }
  },

  methods: {
    getValue: function(str) {
      return eval(
        'this.$store.getters.userData.card_info["' +
          this.selectedCardID +
          '"].info.' +
          str
      );
    }
  }
};
</script>

<style scoped>
.card {
  margin: 5px;
}
.select {
  margin: auto;
}
.resist {
  margin-top: 30vh;
}
</style>