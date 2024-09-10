/**
 @framework_function="RPCClientInterfaceTerminate"
 
   Purpose:  Teardown the RPC client interface by unbinding and freeing the handles.            <br>
                                                                                                <br>
   Notes:                                                                                       <br>
                                                                                                <br>
   MSDN_Ref: HTTP://MSDN.Microsoft.com/En-US/Library/Windows/Desktop/AA378651.aspx              <br>
             HTTP://MSDN.Microsoft.com/En-US/Library/Windows/Desktop/AA375613.aspx              <br>
             HTTP://MSDN.Microsoft.com/En-US/Library/Windows/Desktop/AA375588.aspx              <br>
*/
UINT32 RPCClientInterfaceTerminate()
{
   RPC_STATUS status = RPC_S_OK;

   if(pRPCData &&
      pRPCData->bindingHandle)
   {
      if(pRPCData->isBound)
      {
         status = RpcBindingUnbind(pRPCData->bindingHandle);
         if(status != RPC_S_OK)
            HlprLogError(L"RPCClientInterfaceTerminate : RpcBindingUnbind() [status: %#x]",
                         status);
         else
            pRPCData->isBound = FALSE;
      }

      status = RpcBindingFree(&(pRPCData->bindingHandle));
      if(status != RPC_S_OK)
         HlprLogError(L"RPCClientInterfaceTerminate : RpcBindingFree() [status: %#x]",
                      status);
   }

   HLPR_DELETE(pRPCData);

   return status;
}