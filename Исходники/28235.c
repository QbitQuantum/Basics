//--------------------------------------------------------------------------------
// print shellcode
//--------------------------------------------------------------------------------
void PrintSc(char *lpBuff, int buffsize)
{
   int i,j;
   char *p;
   char msg[4];

   for(i=0;i<buffsize;i++)
   {
       if((i%16)==0)
       {
           if(i!=0)
               printf("\"\n\"");
           else
               printf("\"");
       }

       sprintf(msg, "\\x%.2X", lpBuff[i] & 0xff);

       for( p = msg, j=0; j < 4; p++, j++ )
       {
           if(isupper(*p))
               printf("%c", _tolower(*p));
           else
               printf("%c", p[0]);
       }
   }
   printf("\";\n");
}