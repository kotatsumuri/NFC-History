<template>
	<v-app>
		<page-header/>
		<v-content>
			<v-container fluid>
				<router-view/>
			</v-container>
		</v-content>
	</v-app>
</template>

<script>
import PageHeader from './components/PageHeader'

export default {
	name: 'App',

	components: {
		PageHeader
	}

};
</script>
