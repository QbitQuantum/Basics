bool WEAPRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }