int main()
{
	char *filename;
	FILE *f1,*f2;
	int i,number;
	f1=fopen("TEST","w");
	for(i=10;i<=100;i++)
	{
		putw(i,f1);
	}
	fclose(f1);
	printf("\nInput filename\n");
	open_file:
	scanf("%s",filename);
	if((f2=fopen(filename,"r"))==NULL)
	{
		printf("Can not open the file.\n");
		printf("Type filena,e again.\n");
		goto open_file;
	}
	else
	for(i=1;i<=20;i++)
	{
		number=getw(f2);
		if(feof(f2))
		{
			printf("Ran out of data.\n");
			break;
		}
		else 
		printf("%d\n",number);
	}
	fclose(f2);
}