void additem()
{
	fclose(fsal);
	int b;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	sal1.id=0;
	sal1.price=0;
	sal1.quan=0;
	int id;
	gtc(45,13);printf("Input Item ID: ");scanf("%d",&id);
	fi1=fopen("mainInv.data","rb+");
	while(fread(&inv1,sizeof(inv1),1,fi1)==1)
	{
	if (cID(id)==0)
	{
		gtc(45,14);printf("Item Matched! \(%s)",inv1.pName);
		gtc(45,15);printf("Input Quantity: ");scanf("%d",&sal1.quan);
		for(int a=0;a<=6;a++)
		{
			sal1.name[a]=inv1.pName[a];
		}
		srand(time(NULL));
		b=rand()%100+1;
		sal1.id=inv1.itemID+b;
		sal1.totalquan+=sal1.quan;	
		sal1.price=inv1.price*sal1.quan;
		sal1.total+=sal1.price;
		fsal=fopen("tempsales.data","ab+");
		fseek(fsal,0,SEEK_END);
		fwrite(&sal1,sizeof(sal1),1,fsal);
		fclose(fsal);
		gtc(45,16);printf("Added %d of %s",sal1.quan,inv1.pName);	getch();			
		sales();exit(0);
	}
	else
	{