int main()
{	
	char tab[99]="abc";
	char tab2[99]="abc";
	strcat(tab,tab2);//³¹czy ³añcuchy
	printf("strcat = %s\n",tab);
	strcpy(tab,"abc");strcpy(tab2,"def");
	printf("strcmp = %d\n",strcmp(tab,tab2));//potuwnuje ³añcuchy 0 jak takie same -1 jak ró¿ne
	strcpy(tab,"abc");strcpy(tab2,"def");
	printf("strchr = %d\n",strchr(tab,"b"));//zwraca adres pierwszej litery b strrchr ostatniej
	strset(tab,'x');//wype³nia znekiem x ca³¹ tablicê lib od któregoœ jej momentu
	printf("strset = %s\n",tab);
	strcpy(tab,"abc");
	strupr(tab);//na du¿e
	printf("strupr = %s\n",tab);
	strlwr(tab);//na ma³e
	printf("strlwr = %s\n",tab);



	//i wiele wiele innych




	system("PAUSE");	
	return 0;
}