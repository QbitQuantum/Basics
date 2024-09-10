void RenderUpdateSystem::UpdateActiveIndexes(Entity *entity, RenderObject *object)
{
    Entity *parent;
    
    // search effective lod index
    parent = entity;
    while(NULL != parent)
    {
        LodComponent *lc = GetLodComponent(parent);
        if(NULL != lc)
        {
            object->SetLodIndex(lc->currentLod);
            break;
        }

        parent = parent->GetParent();
    }

    // search effective switch index
    parent = entity;
    while(NULL != parent)
    {
        SwitchComponent *sc = GetSwitchComponent(parent);
        if(NULL != sc)
        {
            object->SetSwitchIndex(sc->GetSwitchIndex());
            break;
        }

        parent = parent->GetParent();
    }
}