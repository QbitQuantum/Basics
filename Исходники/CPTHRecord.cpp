bool CPTHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(CTDA.IsLoaded())
        for(uint32_t ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
            CTDA.value[ListIndex].VisitFormIDs(op);
    if(ANAM.IsLoaded())
        for(uint32_t ListIndex = 0; ListIndex < ANAM.value.size(); ListIndex++)
            op.Accept(ANAM.value[ListIndex]);
    if(SNAM.IsLoaded())
        for(uint32_t ListIndex = 0; ListIndex < SNAM.value.size(); ListIndex++)
            op.Accept(SNAM.value[ListIndex]);

    return op.Stop();
    }