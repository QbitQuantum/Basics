int main()
{
   set_terminate(my_terminate) ;
   try
   {
      throw 1 ;  // no catch block
   }
   catch(const char* message)
   {
      printf( "%s\n", message );
      _fail;
   }
   _PASS;
}