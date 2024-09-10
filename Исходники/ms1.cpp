void stop() {
HandleOutput("hel2mos stop-\n");
	if (hConvExtra) {
		DdeDisconnect ( hConvExtra );
	}
	if (idInst) {
		DdeFreeStringHandle ( idInst, hszService );
		DdeFreeStringHandle ( idInst, hszTopic );
		DdeFreeStringHandle ( idInst, hszItem );
	}
}