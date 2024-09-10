bool RGDLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(XNAM.IsLoaded())
        op.Accept(XNAM.value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM.value);

    return op.Stop();
    }