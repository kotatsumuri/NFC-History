<template>
    <div class = "welcome">
        <div class = "abst">
            <div class = "text-center display-3">NFC-History</div>
            <blockquote class = "text-center blockquote">
                交通系ICのデータの統計を<br class = "d-flex d-sm-none"/>取ることができるサービスです
            </blockquote>
        </div>
        <div class = "text-center">
            <sign-up class = "ma-2"></sign-up>
            <login class = "ma-2"></login>
        </div>
    </div>
</template>

<script>
import SignUp from '../components/SignUp';
import Login from '../components/Login';

export default {
    name: 'Welcome',

    components: {
        SignUp,
        Login,
    }
}
</script>

<style scoped>
.abst {
    margin-top: 20vh;
}
</style>