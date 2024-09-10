bool CSNORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if (DATA.IsLoaded())
        {
        op.Accept(DATA->currency);
        op.Accept(DATA->winningsQuest);
        }

    return op.Stop();
    }