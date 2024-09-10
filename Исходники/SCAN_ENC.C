main(int argc,char *argv[])
{
    long int i,j,k,l,n1,n2,nl;
    if(argc==3)
    {
        clrscr();

        fp1=fopen(argv[1],"rb");
        fp2=fopen(file3,"wb");

        fseek(fp1,0,2);
        l=ftell(fp1);
        n1=l/32;
        n2=l%32;
        fseek(fp1,0,0);
        nl=0;
        for(i=0; i<16; i++)
            for(j=0; j<16; j++)
                mat[i][j]= nl++;
        clrscr();
        keygen();
        /* To envoke randomizetion() function secure-times */
        for(i=1; i<=secure; i++)
            randomization();
        for(i=1; i<=n1; i++)
        {
            fread(&data1,sizeof(data1),1,fp1);
            bit_stream(data1.ch);
            encrypt_bit();
        }

        if (n2!=0)
        {
            for(i=0; i<n2; i++)
            {
                fscanf(fp1,"%c",&data2[i]);
                data2[i]=rshift_residual(data2[i],5);
                /*data2[i]=data2[i]^255;*/
                fprintf(fp2,"%c",data2[i]);
            }
        }

        fcloseall();
        /*msa_encryption(file3,file2);*/
        msa_encryption(file3,argv[2]);

        printf("\nData encryption is over.\n\n");
        getch();
    }
    else
        printf("\n***Invalid command line arguments***\n");
}