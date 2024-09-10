HGLOBAL
GlobalFreeP(
   HGLOBAL hglbMem
)
{
   HGLOBAL hReturn;
   DWORD   dwSize;

   // get size of block before freeing it
   dwSize = (DWORD) GlobalSize(hglbMem);
   if (dwSize > 0)
   {
      // size was obtained OK so free the block
      hReturn = GlobalFree(hglbMem);
      if (hReturn == NULL)
      {
         // memory was freed
         if (pAppData != NULL)
         {
            // update call count
            pAppData->dwFreeCalls ++;
            pAppData->dwApplicationBytes -= dwSize;
         }
      }
      else
      {
         // memory was not freed so don't change data
      }
   }
   else
   {
      // unable to read memory size
   }
   return hReturn;
}