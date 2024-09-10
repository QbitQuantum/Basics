bool DIALRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < QSTI.value.size(); ListIndex++)
        op.Accept(QSTI.value[ListIndex]);

    for(uint32_t ListIndex = 0; ListIndex < QSTR.value.size(); ListIndex++)
        op.Accept(QSTR.value[ListIndex]);

    return op.Stop();
    }