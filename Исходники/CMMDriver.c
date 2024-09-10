static void ReleaseAllocMem(ALLOC_MEM_T *node, CODEC_MEM_CTX *CodecMem)
{
    FREE_MEM_T *free_node;
    BOOL        r;

    __try
    {
        printD("decommit CodecAddr\n");
        r = VirtualFreeEx(CodecMem->callerProcess,    // HANDLE hProcess
                          node->u_addr,
                          0,
                          MEM_RELEASE);
        if (r == FALSE)
        {
            RETAILMSG(1, (L"[%d][CMM_Close] CMM VirtualFreeEx returns FALSE.(u_addr : 0x%08x cacheFlag : %d callerprocess:%ld)\n", 
            CodecMem->inst_no, node->u_addr, node->cacheFlag, CodecMem->callerProcess));
        }

        free_node = (FREE_MEM_T    *)malloc(sizeof(FREE_MEM_T));
        free_node->startAddr = node->cached_p_addr;
        free_node->size = node->size;
        InsertNodeToFreeList(free_node, CodecMem->inst_no);

        // Delete from AllocMem list
        DeleteNodeFromAllocList(node, CodecMem->inst_no);
    }
    __except ( EXCEPTION_EXECUTE_HANDLER )
    {
        RETAILMSG( 1, ( _T("CMM ReleaseAllocMem exception occurred\n")) );
    }
}