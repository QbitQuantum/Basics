InterfaceDatabase::~InterfaceDatabase()
{
   try
   {
      if (conn_)
      {
         RollbackTransaction();
      }
   }
   catch (...)
   {

   }
}