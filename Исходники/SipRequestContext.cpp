// Copy constructor
SipRequestContext::SipRequestContext(const SipRequestContext& rSipRequestContext)
{
   // delete the old values in the UtlDList
   if(!mVariableList.isEmpty())
   {
      mVariableList.destroyAll();
   }

   //copy mVariableList memebers individually
	UtlDListIterator iterator((UtlDList&)rSipRequestContext.mVariableList);
	NameValuePair* nameValuePair = NULL;
   UtlString value;
   UtlString name;
   int index = 0;
   do
   {
      nameValuePair = (NameValuePair*)iterator();
      if(nameValuePair)
      {
         name.append(*nameValuePair);
         value.append(nameValuePair->getValue());
         NameValuePair* newNvPair = new NameValuePair(name, value);
         mVariableList.insertAt(index, newNvPair);
         index ++;
         name.remove(0);
         value.remove(0);
      }
   }
   while (nameValuePair != NULL);
}