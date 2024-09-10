bool FLORRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(PFIG.IsLoaded())
        op.Accept(PFIG.value);

    return op.Stop();
    }