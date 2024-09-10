bool WTHRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(_0IAD.IsLoaded())
        op.Accept(_0IAD.value);
    if(_1IAD.IsLoaded())
        op.Accept(_1IAD.value);
    if(_2IAD.IsLoaded())
        op.Accept(_2IAD.value);
    if(_3IAD.IsLoaded())
        op.Accept(_3IAD.value);
    if(_4IAD.IsLoaded())
        op.Accept(_4IAD.value);
    if(_5IAD.IsLoaded())
        op.Accept(_5IAD.value);
    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    for(uint32_t x = 0; x < Sounds.value.size(); x++)
        op.Accept(Sounds.value[x]->sound);

    return op.Stop();
    }