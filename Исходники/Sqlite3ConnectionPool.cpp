PooledConnection* Sqlite3ConnectionPool::createConnection()
{
   PooledConnection* rval = NULL;

   // create and connect connection
   Connection* c = new Sqlite3Connection();
   if(c->connect(&mUrl))
   {
      // wrap in a pooled connection
      rval = new PooledConnection(this, c);
   }
   else
   {
      delete c;
   }

   return rval;
}