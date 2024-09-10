void LodNode::RecheckLod()
{
//#define LOD_DEBUG
    if (!currentLod)return;

    if (INVALID_LOD_LAYER != forceLodLayer) 
    {
        for (List<LodData>::iterator it = lodLayers.begin(); it != lodLayers.end(); it++)
        {
            if (it->layer >= forceLodLayer)
            {
                currentLod = &(*it);
                return;
            }
        }
            return;
    }
    
#ifdef LOD_DEBUG
    int32 cl = currentLod->layer;
#endif
    {
        float32 dst = 0.f;
        if(INVALID_DISTANCE == forceDistance)
        {
            if(scene->GetCurrentCamera())
            {
                dst = (scene->GetCurrentCamera()->GetPosition() - GetWorldTransform().GetTranslationVector()).SquareLength();
                dst *= scene->GetCurrentCamera()->GetZoomFactor() * scene->GetCurrentCamera()->GetZoomFactor();
            }
        }
        else 
        {
            dst = forceDistanceSq;
        }
        
        if (dst > GetLodLayerFarSquare(currentLod->layer) || dst < GetLodLayerNearSquare(currentLod->layer))
        {
            for (List<LodData>::iterator it = lodLayers.begin(); it != lodLayers.end(); it++)
            {
                if (dst >= GetLodLayerNearSquare(it->layer))
                {
                    currentLod = &(*it);
                }
                else 
                {
#ifdef LOD_DEBUG
                    if (cl != currentLod->layer) 
                    {
                        Logger::Info("Switch lod to %d", currentLod->layer);
                    }
#endif
                    return;
                }
            }
        }
    }
#ifdef LOD_DEBUG
    if (cl != currentLod->layer) 
    {
        Logger::Info("Switch lod to %d", currentLod->layer);
    }
#endif
}