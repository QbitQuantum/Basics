bool LVLNRecord::VisitFormIDs(FormIDOp &op)
    {
        if(!IsLoaded())
            return false;

        for(UINT32 x = 0; x < Entries.value.size(); x++)
            {
            op.Accept(Entries.value[x]->LVLO.value.listId);
            if(Entries.value[x]->IsGlobal())
                op.Accept(Entries.value[x]->COED->globalOrRank);
            }
        return op.Stop();
    }