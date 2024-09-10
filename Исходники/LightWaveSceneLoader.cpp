bool LightWaveSceneLoader::LoadFromFile( const std::string& filepath )
{
    CTextFileScanner scanner;

    if( !scanner.OpenFile( filepath ) )
        return false;

    // clear the scene currently stored
    Clear();

    string tag, strLine;

    for( ; !scanner.End(); scanner.NextLine() )
    {
        // used in scene file with version 5 or later
        string item_id_in_hex;
//		int item_id = -1;

        scanner.GetTagString( tag );
        scanner.GetCurrentLine( strLine );

        /*		if( 0 < m_vecObjectLayer.size() &&
        			m_vecObjectLayer.back().LoadFromFile( scanner ) )
        			continue;

        		if( 0 < m_vecLight.size() &&
        			m_vecLight.back().LoadFromFile( scanner ) )
        			continue;*/

        if( m_SceneInfo.LoadSceneInfo( scanner ) )
            continue;

        if( 0 < m_vecpItem.size() && m_vecpItem.back()->LoadFromFile( scanner ) )
        {
            continue;
        }

        if( tag == "LoadObjectLayer" )
        {
            m_vecObjectLayer.push_back( shared_ptr<LWS_ObjectLayer>( new LWS_ObjectLayer() ) );
            if( 5 <= m_SceneInfo.m_Version )
            {
                scanner.ScanLine( tag,
                                  m_vecObjectLayer.back()->m_iLayerNumber,
                                  item_id_in_hex,
                                  m_vecObjectLayer.back()->m_strObjectFilename );
            }
            else
            {
                scanner.ScanLine( tag,
                                  m_vecObjectLayer.back()->m_iLayerNumber,
                                  m_vecObjectLayer.back()->m_strObjectFilename );
            }

            m_vecpItem.push_back( m_vecObjectLayer.back().get() );
            m_vecpItem.back()->SetItemID( from_hex_to_int(item_id_in_hex) );

            continue;
        }

        else if( tag == "AddNullObject" )
        {
            m_vecObjectLayer.push_back( shared_ptr<LWS_ObjectLayer>( new LWS_ObjectLayer() ) );
            scanner.ScanLine( tag, m_vecObjectLayer.back()->m_strObjectFilename );
            m_vecObjectLayer.back()->SetNullObject( true );

            m_vecpItem.push_back( m_vecObjectLayer.back().get() );

            continue;
        }

        else if( tag == "AddBone" )
        {
            m_vecpBone.push_back( shared_ptr<LWS_Bone>( new LWS_Bone() ) );

            if( 5 <= m_SceneInfo.m_Version )
                scanner.ScanLine( tag, item_id_in_hex );

            m_vecpItem.push_back( m_vecpBone.back().get() );
            m_vecpItem.back()->SetItemID( from_hex_to_int(item_id_in_hex) );

            continue;
        }

        else if( tag == "AddLight" )
        {
            m_vecLight.push_back( shared_ptr<LWS_Light>( new LWS_Light() ) );

            if( 5 <= m_SceneInfo.m_Version )
                scanner.ScanLine( tag, item_id_in_hex );

            m_vecpItem.push_back( m_vecLight.back().get() );
            m_vecpItem.back()->SetItemID( from_hex_to_int(item_id_in_hex) );

            continue;
        }

        /*		else if( tag == "AddCamera" )
        		{
        			m_vecpCamera.push_back( shared_ptr<LWS_Camera>( new LWS_Camera() ) );

        			if( 5 <= m_SceneInfo.m_Version )
        				scanner.ScanLine( tag, item_id );

        			m_vecpItem.push_back( m_vecpCamera.back().get() );
        			m_vecpItem.back()->SetItemID( item_id );

        			continue;
        		}
        */
        else if( tag == "AmbientColor" )
        {
            scanner.ScanLine( tag, m_afAmbientColor[0], m_afAmbientColor[1], m_afAmbientColor[2] );
            continue;
        }

        else if( tag == "AmbientIntensity" )
        {
            scanner.ScanLine( tag, m_fAmbientIntensity );
            continue;
        }

        else if( LoadFogDataBlock(scanner) )
            continue;

    }

    UpdateItemTrees();

    /// create links from parent items to child items
    AddParentToChildLinks();

    return true;
}