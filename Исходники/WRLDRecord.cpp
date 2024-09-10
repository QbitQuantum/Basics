bool WRLDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(XEZN.IsLoaded())
        op.Accept(XEZN.value);
    if(WNAM.IsLoaded())
        op.Accept(WNAM.value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM.value);
    op.Accept(NAM2.value);
    op.Accept(NAM3.value);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    for(UINT32 ListIndex = 0; ListIndex < IMPS.value.size(); ListIndex++)
        {
        op.Accept(IMPS.value[ListIndex]->oldImpact);
        op.Accept(IMPS.value[ListIndex]->newImpact);
        }

    return op.Stop();
    }