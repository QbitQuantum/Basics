bool SHOURecord::VisitFormIDs(FormIDOp &op)
{
    if (!IsLoaded())
        return false;

    if (MDOB.IsLoaded())
        op.Accept(MDOB.value);

    for (uint32_t x = 0; x < SNAM.value.size(); ++x)
    {
        op.Accept(SNAM.value[x].word);
        op.Accept(SNAM.value[x].spell);
    }

    return op.Stop();
}