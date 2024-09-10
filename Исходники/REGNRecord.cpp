bool REGNRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(WNAM.IsLoaded())
        op.Accept(WNAM.value);
    for(uint32_t ListIndex = 0; ListIndex < Entries.value.size(); ListIndex++)
        {
        for(uint32_t ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDOT.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDOT.value[ListX2Index].objectId);
        for(uint32_t ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDGS.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDGS.value[ListX2Index].grass);
        for(uint32_t ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDSD.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDSD.value[ListX2Index].sound);
        for(uint32_t ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDWT.value.size(); ListX2Index++)
            {
            op.Accept(Entries.value[ListIndex]->RDWT.value[ListX2Index].weather);
            op.Accept(Entries.value[ListIndex]->RDWT.value[ListX2Index].globalId);
            }
        if(Entries.value[ListIndex]->RDMO.IsLoaded())
            op.Accept(Entries.value[ListIndex]->RDMO.value);
        if(Entries.value[ListIndex]->RDSI.IsLoaded())
            op.Accept(Entries.value[ListIndex]->RDSI.value);
        for(uint32_t ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDSB.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDSB.value[ListX2Index]);
        for(uint32_t ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDID.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDID.value[ListX2Index]);
        }

    return op.Stop();
    }