bool WATRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(XNAM.IsLoaded())
        op.Accept(XNAM.value);
    op.Accept(GNAM.value.dayWater);
    op.Accept(GNAM.value.nightWater);
    op.Accept(GNAM.value.underWater);

    return op.Stop();
    }