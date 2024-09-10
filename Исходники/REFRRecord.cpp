bool REFRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(Data.IsLoaded())
        {
        op.Accept(Data->NAME.value);
        if(Data->XTEL.IsLoaded())
            op.Accept(Data->XTEL->destinationFid);
        if(Data->XLOC.IsLoaded())
            op.Accept(Data->XLOC->key);
        if(Data->Ownership.IsLoaded())
            {
            if(Data->Ownership->XOWN.IsLoaded())
                op.Accept(Data->Ownership->XOWN.value);
            if(Data->Ownership->XGLB.IsLoaded())
                op.Accept(Data->Ownership->XGLB.value);
            }
        if(Data->XESP.IsLoaded())
            op.Accept(Data->XESP->parent);
        if(Data->XTRG.IsLoaded())
            op.Accept(Data->XTRG.value);
        if(Data->XPCI.IsLoaded() && Data->XPCI->XPCI.IsLoaded())
            op.Accept(Data->XPCI->XPCI.value);
        if(Data->XRTM.IsLoaded())
            op.Accept(Data->XRTM.value);
        }

    return op.Stop();
    }