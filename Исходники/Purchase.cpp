// HandleMessageForBuyThread runs in the context of the buy thread.
HRESULT HandleMessageForBuyThread(
   MSG* pMsg,
   CONTENT_PARTNER_THREAD_CONTEXT* pThreadCtx, 
   CComPtr<IWMPContentPartnerCallback> spCallback)
{
   BUY_CONTEXT* pBuyCtx = NULL;
   HRESULT hr = S_OK; 
   CComPtr<IWMPContentContainerList> spContainerList = NULL;
   ULONG numContainers = 0;

   if(NULL == pMsg || NULL == pThreadCtx || NULL == spCallback)
   {
      hr = E_INVALIDARG;
      goto cleanup;
   }

   if(pThreadCtx->buyThreadContext.msgBuy == pMsg->message)
   {
      // We must handle this message and free the message context.

      ATLTRACE2("%x: HandleMessageForBuyThread: Received message to buy.\n", GetCurrentThreadId());     

      pBuyCtx = reinterpret_cast<BUY_CONTEXT*>(pMsg->lParam);

      if(NULL == pBuyCtx)
      {
         hr = E_UNEXPECTED;
         goto cleanup;
      }

      if(NULL == pBuyCtx->pIStream)
      {
         hr = E_UNEXPECTED;
         goto cleanup;
      }

      // Get a pointer to an IWMPContentContainerList interface.

      hr = CoGetInterfaceAndReleaseStream(
         pBuyCtx->pIStream,
         __uuidof(IWMPContentContainerList),
         reinterpret_cast<LPVOID*>(&spContainerList) );

      // The stream was released (even if CoGetInterfaceAndReleaseStream failed). 
      // Set the stream pointer to NULL.
      pBuyCtx->pIStream = NULL;

      if(FAILED(hr))
      {
         ATLTRACE2("%x: HandleMessageForBuyThread: Failed to get IWMPContentContainerList interface. %x\n", GetCurrentThreadId(), hr);     
         goto cleanup;
      }

      if(NULL == spContainerList)
      {
         hr = E_UNEXPECTED;
         goto cleanup;
      }

      ATLTRACE2("%x: HandleMessageForBuyThread: Successfully obtained IWMPContentContainerList interface.\n", GetCurrentThreadId());
         
      hr = spContainerList->GetContainerCount(&numContainers);

      if(FAILED(hr))
      {
         ATLTRACE2("%x: HandleMessageForBuyThread: GetContainerCount failed. %x\n", GetCurrentThreadId(), hr);
         goto cleanup;
      }

      ATLTRACE2("%x: HandleMessageForBuyThread: numContainers = %d.\n", GetCurrentThreadId(), numContainers);

      for(ULONG j = 0; j < numContainers; ++j)
      {
         ULONG numItems = 0;
         CComPtr<IWMPContentContainer> spContainer;

         hr = spContainerList->GetContainer(j, &spContainer);

         if(FAILED(hr))
         {
            break;  // Break out of the for-j loop.
         }
   
         hr = spContainer->GetContentCount(&numItems);

         if(FAILED(hr))
         {
            // Make sure we don't enter the for-k loop.
            numItems = 0;
         }    

         for(ULONG k = 0; k < numItems; ++k)
         {
            ULONG itemID = 0;

            hr = spContainer->GetContentID(k, &itemID);

            if(FAILED(hr))
            {
               break;  // Break out of the for-k loop.
            }

            // ToDo: Update records to reflect the purchase of this item.

            ATLTRACE2("%x: HandleMessageForBuyThread: Buying item %d.\n",GetCurrentThreadId(), itemID);

         } // for k
      } // for j   

      // Tell Windows Media Player that we have finished 
      // processing the purchase request.

      hr = spCallback->BuyComplete(S_OK, pBuyCtx->cookie);

      if(FAILED(hr))
      {
         ATLTRACE2("%x: HandleMessageForBuyThread: Failed to notify Windows Media Player that a purchase is complete. %x\n", GetCurrentThreadId(), hr);
         goto cleanup;
      }
   } // buy message

   else
   {
      ATLTRACE2("%x: HandleMessageForBuyThread: Received unrecognized message. %x\n", GetCurrentThreadId(), pMsg->message);
   }
    
cleanup:

   if(NULL != pThreadCtx && NULL != pMsg)
   {

      if(pThreadCtx->buyThreadContext.msgBuy == pMsg->message)
      {
         // The thread that posted this message allocated a 
         // BUY_CONTEXT structure.
         // We must free that memory here.

         if(NULL != pBuyCtx)
         {
            if(NULL != pBuyCtx->pIStream)
            {
               pBuyCtx->pIStream->Release();
               pBuyCtx->pIStream = NULL;
            }

            delete pBuyCtx;
            pBuyCtx = NULL;
         }
      }
   }
   return hr;
}