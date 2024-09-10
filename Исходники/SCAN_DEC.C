	void msa_decryption(char file1[],char file3[])
	{
	char file4[50]={'T','E','M','P','1','.','D','A','T','\0'};
	long int i,nrec,nloop,flag,n1;
	int a;
	unsigned char ch;
	clrscr();
	nrec=0;

	/*keygen();
	randomization();*/

	fp1=fopen(file1,"rb");
	fp2=fopen(file4,"wb");
	n1=0;
	while(fscanf(fp1,"%c",&ch)>0)
	{
	fprintf(fp2,"%c",ch);
	n1++;
	}
	fcloseall();
	for(a=0;a<secure;a++)
	{
	fp1=fopen(file4,"rb");
	fp2=fopen(file3,"wb");
		while(fscanf(fp1,"%c",&ch)>0)
		nrec++;
	rewind(fp1);
	nloop=nrec/2;
		if((nrec%2)!=0)
		flag=1;
		else
		flag=0;
		for(i=1;i<=nloop;i++)
		{
		fread(&mydata1,sizeof(mydata1),1,fp1);
			if(mydata1.str[0] == mydata1.str[1])
			{
			decrypt1(mydata1.str[0],mat);
			decrypt1(mydata1.str[1],mat);
			}
			else
			decrypt(mydata1.str[0],mydata1.str[1],mat);
		}
		if(flag==1)
		{
		fscanf(fp1,"%c",&ch);
		fprintf(fp2,"%c",ch);
		}
	fcloseall();
	nrec=0;
	fp1=fopen(file3,"rb");
	fp2=fopen(file4,"wb");
		while(fscanf(fp1,"%c",&ch)>0)
		fprintf(fp2,"%c",ch);
	fcloseall();
	}  /*End of Decryption Process*/
	/* system("del TEMP.DAT"); */ /*  Removing temporary file */
	}