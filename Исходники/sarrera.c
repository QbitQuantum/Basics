int SARRERA_aukerakAukeratu(){
	int bukatu = 0;
	int tekla = 0;
	int posizioa = 1;
	
	SARRERA_jokoarenAukerak(130, 90 + 50 * posizioa, 200, 30);

	do{
		tekla = ebentoaEntzun();
		if (tekla == TECLA_UP){
			if (posizioa > 1){
				posizioa = posizioa - 1;
			}
		}
		if (tekla == TECLA_DOWN){
			if (posizioa <AUKERAKOPURUA){
				posizioa = posizioa + 1;
			}
		}

		if ((tekla == TECLA_UP) || (tekla == TECLA_DOWN)){
			SARRERA_jokoarenAukerak(130, 90 + 50 * posizioa, 200, 30);
		}

		if (tekla == TECLA_RETURN){
			bukatu = 1;
			_sleep(100);
		}
		
	}while(bukatu==0);

	//return
	return posizioa;

}