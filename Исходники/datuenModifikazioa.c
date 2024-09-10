int DATUENMODIFIKAZIOA_ikasgaiakSartuAdministrazioa(ESKOLA *ptr_eskola){
	//aldagaiak
	int kont = 0;
	int maila = 0;
	int i = 0;
	int aukera = 0;
	int jarraitu = 1;

	//programa
	printf("Momentuz sortuta dauden ikasgaiak hauek dira:\n");

	for (i = 0; i < IKASGAIMAX; i++){
		if (ptr_eskola->ikasgaiak[i].id!=0){
			printf("%i. %s\n", ptr_eskola->ikasgaiak[i].id, ptr_eskola->ikasgaiak[i]);
		}
		else{
			break;
		}
	}
	printf("Ikasgai berriaren izena sartu: ");
	gets_s(ptr_eskola->ikasgaiak[i].izena, IZENAMAX);
	ptr_eskola->ikasgaiak[i].id = i + 1;

	system("cls");

}