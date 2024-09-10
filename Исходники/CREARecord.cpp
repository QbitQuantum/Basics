bool CREARecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < SPLO.value.size(); ListIndex++)
        op.Accept(SPLO.value[ListIndex]);
    for(uint32_t ListIndex = 0; ListIndex < SNAM.value.size(); ListIndex++)
        op.Accept(SNAM.value[ListIndex]->faction);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    for(uint32_t ListIndex = 0; ListIndex < CNTO.value.size(); ListIndex++)
        op.Accept(CNTO.value[ListIndex]->item);
    for(uint32_t ListIndex = 0; ListIndex < PKID.value.size(); ListIndex++)
        op.Accept(PKID.value[ListIndex]);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    if(CSCR.IsLoaded())
        op.Accept(CSCR.value);
    for(uint32_t ListIndex = 0; ListIndex < Sounds.value.size(); ListIndex++)
        op.Accept(Sounds.value[ListIndex]->CSDI.value);

    return op.Stop();
    }