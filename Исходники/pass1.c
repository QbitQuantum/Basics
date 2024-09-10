void main()
{
 char oppcde[10],oprnd[10],lable[10],cde[10][10],chh;
 char mnm[20][20]={"PROG","LDCH","STCH","END"};//MENMONICS USED
 int loctre,strt,lengt,i=0,j=0;
 FILE *fp4,*fp5,*fp6;//FILE POINTERS
 fp4=fopen("INPUT.DAT","r");//OPENING INPUT FILE IN READ MODE
 fp5=fopen("SYM.DAT","w");
 fp6=fopen("OUT.DAT","w");
 fscanf(fp4,"%s%s%s",lable,oppcde,oprnd);
 if(strcmp(oppcde,"PROG")==0)//CHECKING STARTING SYMBOL
  {
   strt=atoi(oprnd);
   loctre=strt;
   fprintf(fp6,"%s\t%s\t%s\n",lable,oppcde,oprnd);
   fscanf(fp4,"%s%s%s",lable,oppcde,oprnd);
  }
 else
  loctre=0;
 while(strcmp(oppcde,"END")!=0)
  {
   fprintf(fp6,"%d",loctre);
   if(strcmp(lable,"**")!=0)
     fprintf(fp5,"%s\t%d\n",lable,loctre);
   strcpy(cde[i],mnm[j]);
   while(strcmp(mnm[j],"END")!=0)
    {
     if(strcmp(oppcde,mnm[j])==0)
     {
      loctre+=3;
      break;
     }
     strcpy(cde[i],mnm[j]);
     j++;
    }
   if(strcmp(oppcde,"WORD")==0)
    loctre+=3;
   else if(strcmp(oppcde,"RESW")==0)
    loctre+=(3*(atoi(oprnd)));
   else if(strcmp(oppcde,"RESB")==0)
    loctre+=(atoi(oprnd));
   else if(strcmp(oppcde,"BYTE")==0)
    ++loctre;
   fprintf(fp6,"\t%s\t%s\t%s\n",lable,oppcde,oprnd);
   fscanf(fp4,"%s%s%s",lable,oppcde,oprnd);
  }
  fprintf(fp6,"%d\t%s\t%s\t%s\n",loctre,lable,oppcde,oprnd);
  _fcloseall();
  printf("\nThe contents of Input Table :\n");//PRINTING INPUT FILE
  fp4=fopen("INPUT.DAT","r");
  chh=fgetc(fp4);
  while(chh!=EOF)
   {
    printf("%c",chh);
    chh=fgetc(fp4);
   }
  printf("\nThe contents of Output Table :\n\t");//PRINTING OF INTERMEDIATE FILE
  fp6=fopen("OUT.DAT","r");
  chh=fgetc(fp6);
  while(chh!=EOF)
   {
    printf("%c",chh);
    chh=fgetc(fp6);
   }
  printf("\nThe contents of Sym Table :\n");//PRINTING OF SYMTABLE
  fp5=fopen("SYM.DAT","r");
  chh=fgetc(fp5);
  while(chh!=EOF)
   {
    printf("%c",chh);
    chh=fgetc(fp5);
   }
  _fcloseall();
}