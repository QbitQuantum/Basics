void doListOperations()
{
   UtlSList testList;

   // fill the list
   appendCountItems(testList, NUM_PERFORMANCE_STRINGS);
   
   // take the first half off the front
   if (!testList.isEmpty())
   {
      getCountItems(testList, NUM_PERFORMANCE_STRINGS / 2);
   }

   // take the rest off the end by reference
   if (!testList.isEmpty())
   {
      UtlContainable* lastItem = testList.last();
      delete dynamic_cast<UtlString*>(testList.removeReference(lastItem));
   }

   // fill the list
   appendCountItems(testList, NUM_PERFORMANCE_STRINGS);

   // search the list for each item by value
   UtlString target;
   int targetIndex;
   for (targetIndex = 0; targetIndex < NUM_PERFORMANCE_STRINGS; targetIndex += 1)
   {
      target = string[targetIndex];
      UtlString* found = dynamic_cast<UtlString*>(testList.find(&target));
      if (found)
      {
         externalForSideEffects = found->length();
      }
   }
   
   // get the object in the middle of the list by index, and remove it by value
   while(!testList.isEmpty())
   {
      int numberLeft = testList.entries();
      UtlString* middle = dynamic_cast<UtlString*>(testList.at((numberLeft / 2)));
      delete dynamic_cast<UtlString*>(testList.remove(middle));
   }

   // fill the list
   appendCountItems(testList, NUM_PERFORMANCE_STRINGS);

   // iterate over each item in the list
   UtlSListIterator iterate(testList);
   UtlString* item;
   while ((item = dynamic_cast<UtlString*>(iterate())))
   {
      externalForSideEffects = item->length();
      delete item;
   }
}