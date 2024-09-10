bool LANDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t x = 0; x < BTXT.value.size(); ++x)
        op.Accept(BTXT.value[x]->texture);
    for(uint32_t x = 0; x < Layers.value.size(); ++x)
        op.Accept(Layers.value[x]->ATXT.value.texture);
    for(uint32_t x = 0; x < VTEX.value.size(); x++)
        op.Accept(VTEX.value[x]);

    return op.Stop();
    }