bool LSCRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < LNAM.value.size(); ListIndex++)
        {
        op.Accept(LNAM.value[ListIndex]->direct);
        op.Accept(LNAM.value[ListIndex]->indirect);
        }
    if(WMI1.IsLoaded())
        op.Accept(WMI1.value);

    return op.Stop();
    }