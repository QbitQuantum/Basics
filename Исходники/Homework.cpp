int paralelkenar_ciz()
{
	int i, j,boyut;
	paralelkenardonus:
	printf("Paralelkenar'in Boyutu : ");
	scanf_s("%d", &boyut);
	_flushall();
	if (boyut > 1)
	{
	system("cls");
	for (i = 1; i<(boyut); i++) // işlemi (boyut-1) kadar tekrarlar.
	{
		for (j = 0; j<boyut - (i); j++) // (boyut-1)*(boyut -i) kadar boşluk koyar. 
		{
			printf(" ");
		}
		for (j = 0; j <= boyut; j++) // (boyut-1)*(boyut+1) kadar işlemi tekrarlar.
		{
			for (j = 0; j < boyut; j++) // (boyut-1)*(boyut+1)*(boyut+1) kadar * koyar
				printf("*");
		}
		printf("\n"); // (boyut-1) boşluk yazdırdıktan ve boyut adet yıldız koyduktan sonra bir alt satıra iner.Bu işlemi (boyut-1) degeri kadar yapar.
	}
	for (i = 1; i <= (boyut); i++) // boyut kadar yıldız yazdırtır.Boşluk olmayan satır için yazdım.
	{
		printf("*"); 
	}
	}
	else
	{
		goto paralelkenardonus; // paralelkenardonus noktasina geri donuyor.
	}
	printf("\nDevam etmek icin bir tusa basin!");
	_getch();
	system("cls");
	return 0;
}