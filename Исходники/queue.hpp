       DATAHEAD* GetDataHead()  
       {  
           if (NULL != pFreeDataHead)  
           {  
               DATAHEAD* pTempDataHead = pFreeDataHead;  
               pFreeDataHead = pFreeDataHead->pNext;  
 
               return pTempDataHead;  
           }  
 
           if (ReAlloc())  
           {  
               if (NULL != pFreeDataHead)  
               {  
                   DATAHEAD* pTempDataHead = pFreeDataHead;  
                   pFreeDataHead = pFreeDataHead->pNext;  
 
                   return pTempDataHead;  
               }  
           }  
 
           // ASSERT("GetDataHead??NULL?");  
           assert(false);  
           return NULL;  
       }  