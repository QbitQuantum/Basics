inline void  CprobeIGC::GetTarget(const ModelListIGC*  models,
                              IsideIGC*            pside,
                              const Vector&        myPosition,
                              float                dtUpdate,
                              float                accuracy,
                              float                speed,
                              float                lifespan,
                              ObjectType           type,
                              ImodelIGC**          ppmodelMin,
                              float*               pdistance2Min,
                              Vector*              pdirectionMin)
{
    for (ModelLinkIGC*   l = models->first(); (l != NULL); l = l->next())
    {
        ImodelIGC*   pmodel = l->data();

        assert (pmodel->GetObjectType() == type);

        ValidTarget(pmodel, 
                    pside,
                    myPosition,
                    dtUpdate,
                    accuracy,
                    speed,
                    lifespan,
                    type,
                    ppmodelMin,
                    pdistance2Min,
                    pdirectionMin);
    }
}