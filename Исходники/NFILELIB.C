main()
{
int f=TRUE;
clrscr();
fpt = fopen("library.dat","w");
printf("Enter today's date in this format (dd/mm/yy) : ");
scanf("%d/%d/%d",&library.now.day,
		 &library.now.month,
		 &library.now.year);
while (f)
{
	printf("\nwrite name of the book (write \' END \' when finished) : ");
	scanf(" %[^\n]",&library.nob);
	if (strcmp(library.nob,"END") == 0 )
	break;
	library=read(library);
	fwrite(&library , sizeof(record) , 1 , fpt);
	strset(library.nob,' ');

}
fclose(fpt);
getch();
}