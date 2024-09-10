void vboxDispCmSessionCtxAdd(PVBOXDISPCM_SESSION pSession, PVBOXWDDMDISP_CONTEXT pContext)
{
    EnterCriticalSection(&pSession->CritSect);
    RTListAppend(&pSession->CtxList, &pContext->ListNode);
    LeaveCriticalSection(&pSession->CritSect);
}