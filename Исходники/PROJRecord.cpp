bool PROJRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    op.Accept(DATA.value.light);
    op.Accept(DATA.value.flash);
    op.Accept(DATA.value.explosion);
    op.Accept(DATA.value.sound);
    op.Accept(DATA.value.soundCountdown);
    op.Accept(DATA.value.soundDisable);
    op.Accept(DATA.value.defaultWeaponSource);
    return op.Stop();
    }