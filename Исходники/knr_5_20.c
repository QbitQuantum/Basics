int  main(void) /* convert declaration to words */
{
   int i = 0;
   int ret = 0;

   while (gettoken() != EOF) 
   {
//      if (tokentype != '\n')
  //       printf("syntax error\n");
      for (i = 0; i < tab_no; i++)
         printf("\t");
      if (name[0] && datatype[0])
         printf("%s: %s %s\n", name, out, datatype);

      strcpy(datatype, token); 
      out[0] = '\0';
      name[0] = '\0';
      dcl();        
      print_sol();
   }

   return ret;
}