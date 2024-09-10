/* good2() reverses the bodies in the if statement */
static void good2()
{
    if(staticTrue)
    {
        /* FIX: Check the return value of RpcImpersonateClient() for RPC_S_OK */
        if (RpcImpersonateClient(0) != RPC_S_OK)
        {
            exit(1);
        }
        /* We'll leave out most of the implementation since it has nothing to do with the CWE
         * and since the checkers are looking for certain function calls anyway */
    }
}