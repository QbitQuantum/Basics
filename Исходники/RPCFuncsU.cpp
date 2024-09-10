 // this unbinds to the interface after the RPC call
 void __stdcall UnBind()
 {
     RpcStringFree(&StringBinding);
     StringBinding = NULL;
     RpcBindingFree(&winamp_IfHandle);
 }