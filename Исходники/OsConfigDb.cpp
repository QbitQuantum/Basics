// Remove all the key/value pairs starting with the designated prefix
OsStatus OsConfigDb::removeByPrefix(const UtlString& rPrefix) 
{
   OsWriteLock lock(mRWMutex);
   DbEntry* pEntry ;

   UtlSortedListIterator itor(mDb) ;
   while ((pEntry = (DbEntry*) itor()))
   {
       if (pEntry->key.length() >= rPrefix.length())
       {
           UtlString keyPrefix = pEntry->key ;
           keyPrefix.remove(rPrefix.length()) ;
           if (keyPrefix.compareTo(rPrefix, UtlString::ignoreCase) == 0)
           {
               remove(pEntry->key) ;
           }
       }      
   }
   
   return OS_SUCCESS ;
}