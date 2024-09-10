////////////////////////////////////////////////////////////////
//
// CRenderItemManager::GetVisibleTextureNames
//
// Get the names of all streamed in world textures, filtered by name and/or model
//
////////////////////////////////////////////////////////////////
void CRenderItemManager::GetVisibleTextureNames ( std::vector < SString >& outNameList, const SString& strTextureNameMatch, ushort usModelID )
{
    // If modelid supplied, get the model texture names into a map
    std::set < SString > modelTextureNameMap;
    if ( usModelID )
    {
        std::vector < SString > modelTextureNameList;
        m_pRenderWare->GetModelTextureNames ( modelTextureNameList, usModelID );
        for ( std::vector < SString >::const_iterator iter = modelTextureNameList.begin () ; iter != modelTextureNameList.end () ; ++iter )
            modelTextureNameMap.insert ( (*iter).ToLower () );
    }

    SString strTextureNameMatchLower = strTextureNameMatch.ToLower ();

    std::set < SString > resultMap;

    // For each texture that was used in the previous frame
    for ( std::set < CD3DDUMMY* >::const_iterator iter = m_PrevFrameTextureUsage.begin () ; iter != m_PrevFrameTextureUsage.end () ; ++iter )
    {
        // Get the texture name
        SString strTextureName = m_pRenderWare->GetTextureName ( *iter );
        SString strTextureNameLower = strTextureName.ToLower ();

        if ( strTextureName.empty () )
            continue;

        // Filter by wildcard match
        if ( !WildcardMatch ( strTextureNameMatchLower, strTextureNameLower ) )
            continue;

        // Filter by model
        if ( usModelID )
            if ( !MapContains ( modelTextureNameMap, strTextureNameLower ) )
                continue;

        resultMap.insert ( strTextureName );
    }

    for ( std::set < SString >::const_iterator iter = resultMap.begin () ; iter != resultMap.end () ; ++iter )
    {
        outNameList.push_back ( *iter );
    }
}