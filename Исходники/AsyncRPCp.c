// Asynchronous routine. It sends back the notification
// when it is done.
void AsyncFunc(IN PRPC_ASYNC_STATE pAsync,
               IN RPC_BINDING_HANDLE hBinding,
               IN unsigned long nAsychDelay)
{
   int nReply = 1;
   RPC_STATUS status;
   unsigned long nTmpAsychDelay;
   int i;

   if (nAsychDelay < 0)
      nAsychDelay = DEFAULT_ASYNC_DELAY;

   nAsychDelay *= 1000;  // convert to ms

   // We only call RpcServerTestCancel if the call
   // takes longer than ASYNC_CANCEL_CHECK ms
   if (nAsychDelay > ASYNC_CANCEL_CHECK)
   {
      nTmpAsychDelay = nAsychDelay/100;

      for (i = 0; i < 100; i++)
      {
         Sleep(nTmpAsychDelay);

         if (i%5 == 0)
         {
            // Report the progress of the asynchronous function
            fprintf_s(stderr, "\rRunning AsyncFunc (%lu ms) (%d%c) ... ",
                    nAsychDelay, i+5, PERCENT);

            // Check whether the call is cancelled by the client
            status = RpcServerTestCancel(RpcAsyncGetCallHandle(pAsync));
            if (status == RPC_S_OK)
            {
               fprintf_s(stderr, "\nAsyncFunc has been cancelled!!!\n");
               break;
            }
            else if (status != RPC_S_CALL_IN_PROGRESS)
            {
               printf_s("RpcServerTestCancel returned 0x%x\n", status);
               exit(status); 
            }
         }
      }
   }
   else
      Sleep(nAsychDelay);

   printf_s("\nCalling RpcAsyncCompleteCall\n");
   status = RpcAsyncCompleteCall(pAsync, &nReply);
   printf_s("RpcAsyncCompleteCall returned 0x%x\n", status);
   if (status)
      exit(status);
}