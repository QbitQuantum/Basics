/**********************СОРТИРОВКА ПО ДЛИНЕ***************************/
void length(void)
{
 FILE *f,*f1;
 char filename[14],nameoffile[14];
 char c;
 int i,n=0,k;
 instr com;

 window(1,1,80,25);
 textbackground(0);
 textcolor(2);
 clrscr();
 cputs("Введите имя файла-источника данных...");
 scanf("%s",filename);
 cputs("Введите имя файла,в который будут записаны данные...");
 scanf("%s",nameoffile);
 f=fopen(filename,"r");
 f1=fopen(nameoffile,"aw");
 fseek(f,0,SEEK_SET);
 while(!feof(f))
  {
   fread(&com,sizeof(com),1,f);
   n++;
  }
 printf("Мнемокод    Длина  Машинный код\n");
 n--;
 for(k=49;k<=57;k++)
  {
   fseek(f,0,SEEK_SET);
   for(i=0;i<n;i++)
	{
	 c=toascii(k);
	 fread(&com.name,sizeof(com.name),1,f);
	 fread(&com.size,sizeof(com.size),1,f);
	 fread(&com.hex,sizeof(com.hex),1,f);
	 if(com.size[0]==c)
            {
	    fwrite(&com,sizeof(com),1,f1);
	    printf("%s",&com.name);
	    gotoxy(15,wherey());
	    printf("%s",&com.size);
	    gotoxy(18,wherey());
	    printf("%s\n",com.hex);
            }
	}
  }
 fcloseall();
 cputs("Обработка завершена...");
 getch();
}