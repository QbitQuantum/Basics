bool PACKRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(PLDT.IsLoaded() && (PLDT->locType < 2 || PLDT->locType == 4))
        op.Accept(PLDT->locId);

    if(PTDT.IsLoaded() && PTDT->targetType != 2)
        op.Accept(PTDT->targetId);

    for(UINT32 ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);

    return op.Stop();
    }