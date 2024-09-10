void HelloProc(IN OUT PRPC_ASYNC_STATE pAsync, wchar_t * pszString)
{
    wprintf(L"%s\n", pszString);
    Sleep(10000);
    int nReply = 100;
    RPC_STATUS status = RpcAsyncCompleteCall(pAsync, &nReply);
    wprintf(L"RpcAsyncCompleteCall 0x%x\n",status);
}