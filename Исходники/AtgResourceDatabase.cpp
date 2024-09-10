VOID ResourceDatabase::AddBundledResources( PackedResource* pBundledResourceTable )
{
    assert( pBundledResourceTable != NULL );
    m_BundledResources.push_back( pBundledResourceTable );

    RESOURCE* pTags = NULL;
    DWORD dwResourceCount = 0;
    WCHAR strNameTemp[256];
    pBundledResourceTable->GetResourceTags( &dwResourceCount, &pTags );
    DWORD i = 0;
    while( i < dwResourceCount )
    {
        MultiByteToWideChar( CP_ACP, 0, pTags[i].strName, strlen( pTags[i].strName ) + 1, strNameTemp, 256 );
        _wcslwr_s( strNameTemp );
        switch( pTags[i].dwType )
        {
        case RESOURCETYPE_TEXTURE:
            {
                Texture2D* pTexture = new Texture2D();
                pTexture->SetName( strNameTemp );
                pTexture->bFromPackedResource = TRUE;
                DWORD dwOffset = pTags[ i ].dwOffset;
                D3DTexture* pD3DTexture = pBundledResourceTable->GetTexture( dwOffset );
                pTexture->SetD3DTexture( pD3DTexture );
                AddResource( pTexture );
#ifdef PROFILE
                // Report texture to texture tracker
                PIXReportNewTexture( pD3DTexture );
                CHAR strConverted[256];
                strConverted[0] = 0;
                wcstombs_s( 0, strConverted, strNameTemp, _countof(strConverted) );  
                PIXSetTextureName( pD3DTexture, TEXT(strConverted) );
#endif
                break;
            }
        case RESOURCETYPE_CUBEMAP:
            {
                TextureCube* pTexture = new TextureCube();
                pTexture->SetName( strNameTemp );
                pTexture->bFromPackedResource = TRUE;
                DWORD dwOffset = pTags[ i ].dwOffset;
                D3DCubeTexture* pD3DTexture = pBundledResourceTable->GetCubemap( dwOffset );
                pTexture->SetD3DTexture( pD3DTexture );
                AddResource( pTexture );
#ifdef PROFILE
                // Report texture to texture tracker
                PIXReportNewTexture( pD3DTexture );
                CHAR strConverted[256];
                strConverted[0] = 0;
                wcstombs_s( 0, strConverted, strNameTemp, _countof(strConverted) );  
                PIXSetTextureName( pD3DTexture, TEXT(strConverted) );
#endif
               break;
            }
        case RESOURCETYPE_VOLUMETEXTURE:
            {
                TextureVolume* pTexture = new TextureVolume();
                pTexture->SetName( strNameTemp );
                pTexture->bFromPackedResource = TRUE;
                DWORD dwOffset = pTags[ i ].dwOffset;
                D3DVolumeTexture* pD3DTexture = pBundledResourceTable->GetVolumeTexture( dwOffset );
                pTexture->SetD3DTexture( pD3DTexture );
                AddResource( pTexture );
#ifdef PROFILE
                // Report texture to texture tracker
                PIXReportNewTexture( pD3DTexture );
                CHAR strConverted[256];
                strConverted[0] = 0;
                wcstombs_s( 0, strConverted, strNameTemp, _countof(strConverted) );  
                PIXSetTextureName( pD3DTexture, TEXT(strConverted) );
#endif
              break;
            }
        case RESOURCETYPE_VERTEXBUFFER:
        case RESOURCETYPE_INDEXBUFFER:
        case RESOURCETYPE_USERDATA:
        default:
            {
                // not supported yet
                DebugSpew( "Unsupported resource type %d for resource \"%s\".\n", pTags[i].dwType, pTags[i].strName );
                break;
            }
        }
        ++i;
    }
}