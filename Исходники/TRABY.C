void salva(void)
{  FILE *op;
   char nome[30];
   puts("Digite o nome do arquivo:");
   flushall();
   gets(nome);
   if ((op=fopen(nome,"wb"))==NULL)
   {  puts("Arquivo nao pode ser criado.");
      return; }
   if (fwrite(&inf_nota,sizeof(inf_nota),3,op)==1)
   {  puts("Erro na escrita.");
      getch(); }
   fcloseall();
}