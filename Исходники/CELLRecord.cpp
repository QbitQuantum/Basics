bool CELLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < IMPS.value.size(); ListIndex++)
        {
        op.Accept(IMPS.value[ListIndex]->oldImpact);
        op.Accept(IMPS.value[ListIndex]->newImpact);
        }
    op.Accept(LTMP.value);
    for(uint32_t x = 0; x < XCLR.value.size(); x++)
        op.Accept(XCLR.value[x]);
    if(XCIM.IsLoaded())
        op.Accept(XCIM.value);
    if(XEZN.IsLoaded())
        op.Accept(XEZN.value);
    if(XCCM.IsLoaded())
        op.Accept(XCCM.value);
    if(XCWT.IsLoaded())
        op.Accept(XCWT.value);
    if(Ownership.IsLoaded())
        op.Accept(Ownership->XOWN.value);
    if(XCAS.IsLoaded())
        op.Accept(XCAS.value);
    if(XCMO.IsLoaded())
        op.Accept(XCMO.value);
    return op.Stop();
    }