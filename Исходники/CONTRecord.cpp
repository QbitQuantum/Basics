bool CONTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    for(UINT32 ListIndex = 0; ListIndex < CNTO.value.size(); ListIndex++)
        op.Accept(CNTO.value[ListIndex]->item);
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(QNAM.IsLoaded())
        op.Accept(QNAM.value);

    return op.Stop();
    }