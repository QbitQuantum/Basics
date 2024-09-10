// Dump the object's internal state.
void ContactSet::dumpState()
{
   // indented 8, 10, and 12

   OsSysLog::add(FAC_RLS, PRI_INFO,
                 "\t        ContactSet %p mUri = '%s', mSubscriptionEarlyDialogHandle = '%s'",
                 this, mUri.data(), mSubscriptionEarlyDialogHandle.data());

   UtlHashMapIterator itor(mSubscriptions);
   UtlString* handle;
   while ((handle = dynamic_cast <UtlString*> (itor())))
   {
      UtlHashMap* h = dynamic_cast <UtlHashMap*> (itor.value());
      OsSysLog::add(FAC_RLS, PRI_INFO,
                    "\t          mSubscriptions{'%s'} %p",
                    handle->data(), h);
      UtlHashMapIterator itor2(*h);
      UtlString* id;
      while ((id = dynamic_cast <UtlString*> (itor2())))
      {
         UtlString* value = dynamic_cast <UtlString*> (itor2.value());
         int semi = value->index(';');
         if (semi == UTL_NOT_FOUND)
         {
            semi = value->length();
         }
         const char* v = value->data();
         OsSysLog::add(FAC_RLS, PRI_INFO,
                       "\t            id = '%s', Call-Id = '%.*s', URI = '%s'",
                       id->data(), semi, v, v + semi + 1);
      }
   }

   UtlHashMapIterator itor3(mSubscriptionSets);
   while ((handle = dynamic_cast <UtlString*> (itor3())))
   {
      SubscriptionSet* ss = dynamic_cast <SubscriptionSet*> (itor3.value());
      ss->dumpState();
   }
}