void HelloProc2(IN RPC_BINDING_HANDLE hBinding,unsigned char * pszString)
{
    printf_s("%s\n", _strrev(pszString));
}