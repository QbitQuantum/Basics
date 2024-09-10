int ERREALITATE_FISIKOA_pantailaBukaeraHil(){
	int bukatu = 0;
	int tekla = 0;
	int posizioa = 1;

	do{

		tekla = ebentoaEntzun();
		if (tekla == TECLA_UP){
			if (posizioa > 1){
				posizioa = posizioa - 1;
			}
		}
		if (tekla == TECLA_DOWN){
			if (posizioa < 2){
				posizioa = posizioa + 1;
			}
		}

		ERREALITATE_FISIKOA_pantailaBukaeraHilPrintatu(130, 140 + 50 * posizioa, 200, 30);

		if (tekla == TECLA_RETURN){
			bukatu = 1;
		}

		_sleep(10);

	} while (bukatu == 0);

	//return
	return posizioa;
}