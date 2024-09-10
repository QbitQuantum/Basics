int main()
{
   String* str = new String("Insomnium");
   str->displayString();
   std::cout << std::endl;

   Tokens* tokens = new Tokens(str, 'n');
   tokens->displayTokens();

   int num_tokens = tokens->getNumTokens();
   for (int i = 0; i < num_tokens; i++)
   {
      String* token = tokens->getToken(i);
      delete token;
   }
   delete tokens;  //does not delete the individual tokens
   delete str;

   ReadFile* rf = new ReadFile("cds.txt");
   WriteFile* wf = new WriteFile("out.txt");

   while(!rf->eof())
   {
      String* line = rf->readLine();
      wf->writeLine(line);
      delete line;
   }

   rf->close();
   wf->close();
   delete rf;
   delete wf;

   return 0;
}