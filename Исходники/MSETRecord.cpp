bool MSETRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(HNAM.IsLoaded())
        op.Accept(HNAM.value);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);

    return op.Stop();
    }