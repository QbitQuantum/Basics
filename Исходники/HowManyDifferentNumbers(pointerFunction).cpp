int main()
{
	int girilenSayi;
	int basamak4, basamak3, basamak2, basamak1;
	int *x;

	printf("4 basamakli bir sayi giriniz:");
	scanf_s("%d",&girilenSayi);
	x = &girilenSayi;

	islem(x);


	_getch();
	return 0;
}