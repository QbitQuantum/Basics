OGRFeature *OGRWarpedLayer::WarpedFeatureToSrcFeature(OGRFeature* poFeature)
{
    OGRFeature* poSrcFeature = new OGRFeature(m_poDecoratedLayer->GetLayerDefn());
    poSrcFeature->SetFrom(poFeature);
    poSrcFeature->SetFID(poFeature->GetFID());

    OGRGeometry* poGeom = poSrcFeature->GetGeomFieldRef(m_iGeomField);
    if( poGeom != NULL )
    {
        if( m_poReversedCT == NULL )
        {
            delete poSrcFeature;
            return NULL;
        }

        if( poGeom->transform(m_poReversedCT) != OGRERR_NONE )
        {
            delete poSrcFeature;
            return NULL;
        }
    }

    return poSrcFeature;
}