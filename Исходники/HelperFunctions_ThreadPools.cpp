/**
 @helper_function="HlprThreadPoolDataPurge"
 
   Purpose:  Cleanup a THREADPOOL_DATA object.                                                  <br>
                                                                                                <br>
   Notes:                                                                                       <br>
                                                                                                <br>
   MSDN_Ref: HTTP://MSDN.Microsoft.com/En-US/Library/Windows/Desktop/MS682036.aspx              <br>
             HTTP://MSDN.Microsoft.com/En-US/Library/Windows/Desktop/MS682033.aspx              <br>
             HTTP://MSDN.Microsoft.com/En-US/Library/Windows/Desktop/MS682030.aspx              <br>
             HTTP://MSDN.Microsoft.com/En-US/Library/Windows/Desktop/MS682576.aspx              <br>
*/
inline VOID HlprThreadPoolDataPurge(_Inout_ THREADPOOL_DATA* pThreadPoolData)
{
   ASSERT(pThreadPoolData);

   if(pThreadPoolData->pCleanupGroup)
   {
      CloseThreadpoolCleanupGroupMembers(pThreadPoolData->pCleanupGroup,
                                         FALSE,
                                         0);

      CloseThreadpoolCleanupGroup(pThreadPoolData->pCleanupGroup);
   }

   if(pThreadPoolData->pThreadPool)
      CloseThreadpool(pThreadPoolData->pThreadPool);

   DestroyThreadpoolEnvironment(&(pThreadPoolData->callbackEnvironment));

   ZeroMemory(pThreadPoolData,
              sizeof(THREADPOOL_DATA));

   return;
}