void PDF::WriteInteger(const char * name, int integer)
   {
   WriteName(name);
   WriteInteger(integer);
   fputc('\n', file);
   }