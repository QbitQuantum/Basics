/***********************************************************************
 *           NDRSContextUnmarshall [RPCRT4.@]
 */
NDR_SCONTEXT WINAPI NDRSContextUnmarshall(void *pBuff,
                                          ULONG DataRepresentation)
{
    TRACE("(%p %08x)\n", pBuff, DataRepresentation);
    return NDRSContextUnmarshall2(I_RpcGetCurrentCallHandle(), pBuff,
                                  DataRepresentation, NULL,
                                  RPC_CONTEXT_HANDLE_DEFAULT_FLAGS);
}