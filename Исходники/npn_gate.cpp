void NPN_InvalidateRect(NPP instance, NPRect *invalidRect)
{
    if(logger)
        logger->logCall(action_npn_invalidate_rect, (DWORD)instance, (DWORD)invalidRect);

    NPNFuncs.invalidaterect(instance, invalidRect);
}