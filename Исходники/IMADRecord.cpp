bool IMADRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(RDSD.IsLoaded())
        op.Accept(RDSD.value);
    if(RDSI.IsLoaded())
        op.Accept(RDSI.value);

    return op.Stop();
    }