BIZTANLEA datuakJaso(){
	//aldagaiak
	BIZTANLEA biztanle;

	//programa
	printf("Izena: ");
	fflush(stdin);
	gets_s(biztanle.izena, IZENAMAX);

	printf("Abizena: ");
	fflush(stdin);
	gets_s(biztanle.abizena, IZENAMAX);

	printf("Helbidea, kalea: ");
	fflush(stdin);
	gets_s(biztanle.helbidea.kalea, 40);

	printf("Helbidea, zenbakia: ");
	fflush(stdin);
	scanf("%i", &biztanle.helbidea.zenbakia);

	printf("Helbidea, solairua: ");
	fflush(stdin);
	scanf("%i", &biztanle.helbidea.solairua);

	printf("Helbidea, letra: ");
	fflush(stdin);
	gets(biztanle.helbidea.letra);

	printf("Jaiotze urtea: ");
	fflush(stdin);
	scanf("%i", &biztanle.jaiotzeData.urtea);

	printf("Jaiotze hilea: ");
	fflush(stdin);
	scanf("%i", &biztanle.jaiotzeData.hilea);

	printf("Jaiotze eguna: ");
	fflush(stdin);
	scanf("%i", &biztanle.jaiotzeData.eguna);

	printf("Kontu korrontea: ");
	fflush(stdin);
	gets_s(biztanle.kontuKorrontea, KONTUKORRONTEAMAX);

	printf("Zure dni-a (letra gabe): ");
	scanf("%i", &biztanle.kodea);

	//return 
	return biztanle;
}