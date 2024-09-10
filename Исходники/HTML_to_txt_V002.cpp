int main()
{
	//"Texto del que se eliminan cosas a escribir como quotoes y demas"
	//char p1[]="Texto del que se elimi&quot;&quot;&quot;na&quot;n co&quot;sas a es&quot;cribir como&quot; quotoes y de&quot;mas",p2[1024];
	//elimina(p1,p2,"&quot;");
	//char p1[]="Text<kaka>o del que se el<kaka><kaka>iminan cosas a escri<a>bir como quotoes y<kakakaka><><a> demas",p2[1024];
	//elimina(p1,p2,'<','>');



	FILE *strin,*strout;   errno_t err,err1;
//	err= fopen_s(&strin,"data/prueba.htm","r");
	err= fopen_s(&strin,"data/Yahoo.htm","r");
	err1=fopen_s(&strout,"data/out.htm","w");
	if ((err)||(err1)) 	{  printf("ERROR en ficheros");getchar();getchar(); return -1;  }
	char ch;
	long size_buffer1=0,size_buffer2,sizeant=0;
	while(!feof(strin))
	{
		ch=fgetc(strin);
		size_buffer1++;
	}
	printf("Tamano buffer1=%li",size_buffer1);sizeant=size_buffer1;
	rewind(strin);
	char *buffer1=new char[size_buffer1];
	char *buffer2=new char[size_buffer1];
	char *buffer3;
	long i;
	for (i=0;i<(size_buffer1-1);i++)
	{
		buffer1[i]=fgetc(strin);
	}
	buffer1[i]='\0';
	extrae_2(buffer1,buffer2);buffer3=buffer1;buffer1=buffer2;buffer2=buffer3;
	sizeant=size_buffer1;size_buffer1=strlen(buffer1);printf("\nTamano buffer2 1=%li %li",size_buffer1,size_buffer1-sizeant);

	elimina(buffer1,buffer2,"&quot;");buffer3=buffer1;buffer1=buffer2;buffer2=buffer3;
	sizeant=size_buffer1;size_buffer1=strlen(buffer1);printf("\nTamano buffer2 2=%li %li",size_buffer1,size_buffer1-sizeant);

	elimina(buffer1,buffer2,"(EFE)");buffer3=buffer1;buffer1=buffer2;buffer2=buffer3;
	sizeant=size_buffer1;size_buffer1=strlen(buffer1);printf("\nTamano buffer2 3=%li %li",size_buffer1,size_buffer1-sizeant);

	eliminaduplicados(buffer1,buffer2);buffer3=buffer1;buffer1=buffer2;buffer2=buffer3;
	sizeant=size_buffer1;size_buffer1=strlen(buffer1);printf("\nTamano buffer2 4=%li %li",size_buffer1,size_buffer1-sizeant);

	//Imprimo el ultimo buffer. ¡¡OJO!! pudiera ser buffer1 ó 2, el último válido
	printf("\nTamano buffer1 FIN=%li",strlen(buffer1));
	char *ptr;
	ptr=buffer1;
	while(*ptr)
	{
		fputc(*ptr++,strout);
	}
	fputc(*ptr++,strout);//El null del final
	_fcloseall( );
	getchar();getchar();
	return 0;

}