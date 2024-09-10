bool CGmObjAnim3::ReadXML( TiXmlNode* poParent, unsigned int uiCounter )
{
	if( !poParent )
		return false;
	
	static char acTxt_[256];
	if( uiCounter == 0 )
	{
	}
	
	switch ( poParent->Type() )
	{
	case TiXmlNode::DOCUMENT:
		LOG( "XML: Document" );
	break;
	case TiXmlNode::ELEMENT:
	{
		const char *pcName = poParent->Value();
		//LOG( "name: %s\n", pcName );
		if( !strcmp( pcName, "animation" ) )
		{
			LOG( "animation:\n" );
			
			TiXmlElement * poElement = poParent->ToElement();
			if( poElement )
			{
				int iIdx;
				CStr oMeshFileName;
				CArray<CStr> oArrAnimFileName;
				
				TiXmlAttribute* poAttrib = poElement->FirstAttribute();
				while( poAttrib )
				{
					const char *pcName = poAttrib->Name();
					if( !strcmp( pcName, "mesh" ) )
					{
						STRING_COPY( acTxt_, sizeof(acTxt_), poAttrib->Value() );
						LOG( "%s: %s\n", poAttrib->Name(), acTxt_ );
						oMeshFileName = acTxt_;
					}
					else if( SSCANF( pcName, "anim_%d", &iIdx ) == 1 )
					{
						LOG( "%s: %d\n", poAttrib->Name(), iIdx );
						STRING_COPY( acTxt_, sizeof(acTxt_), poAttrib->Value() );
						LOG( "%s: %s\n", poAttrib->Name(), acTxt_ );
						if( iIdx >= int( oArrAnimFileName.GetSize() ) )
							oArrAnimFileName.Resize( iIdx + 1 );
						oArrAnimFileName[iIdx] = acTxt_;
						
					}
					poAttrib = poAttrib->Next();
				}
				
				if( oMeshFileName.GetSize() )
				{
					// Model.
					m_poModel = m_poResMan_->NewModelMD5( oMeshFileName, oArrAnimFileName, false );
					
					const unsigned int uiFrameCountTotal = m_poModel->GetFrameCountTotal();
					const unsigned int uiMeshCount = m_poModel->GetMeshCount();
					const unsigned int uiAnimCount = m_poModel->GetAnimCount();
					
					m_oArrAnim.Resize( uiAnimCount );
					m_oArrAnim.Fill( 0 );
					
					m_poData->SetFrameCount( uiFrameCountTotal );
					unsigned int uiFrameIdx = 0;
					
					for( unsigned int uiAnim=0; uiAnim<uiAnimCount; ++uiAnim )
					{
						//m_poModel->SetAnim( uiAnim );	
						const unsigned int uiFrameCount = m_poModel->GetFrameCount( uiAnim );
						
						CAnim * poAnim = new CAnim;
						m_oArrAnim[uiAnim] = poAnim;
						
						poAnim->SetFrameRate( m_poModel->GetFrameRate( uiAnim ) );
						poAnim->SetFrameCount( uiFrameCount );
						
						for( unsigned int uiFrame=0; uiFrame<uiFrameCount; ++uiFrame )
						{
							CFrame * poFrame = new CFrame;
							m_poData->SetFrame( uiFrameIdx, poFrame );
							poAnim->SetFrameIndex( uiFrame, uiFrameIdx );
							++uiFrameIdx;
							
							poFrame->SetMeshCount( uiMeshCount );

							for( unsigned int uiMesh=0; uiMesh<uiMeshCount; ++uiMesh )
							{
								CGMeshMD5 * poMesh = m_poModel->GetPrecalcMesh( uiMesh, uiFrame, uiAnim );
								ASSERT( poMesh );
								poFrame->SetMesh( uiMesh, poMesh );
							}
						}

						poAnim->Init();
					}
					ASSERT( uiFrameIdx == uiFrameCountTotal );
				}
			}
		}
		else if( m_poModel )
		{
			if( !strcmp( pcName, "action" ) )
			{
				LOG( "action:\n" );
				
				TiXmlElement * poElement = poParent->ToElement();
				if( poElement )
				{
					CAction *poAction = 0;
					
					TiXmlAttribute* poAttrib = poElement->FirstAttribute();
					while( poAttrib )
					{
						const char *pcName = poAttrib->Name();
						if( !strcmp( pcName, "name" ) )
						{
							STRING_COPY( acTxt_, sizeof(acTxt_), poAttrib->Value() );
							LOG( "%s: %s\n", poAttrib->Name(), acTxt_ );
							
							poAction = new CAction;
							poAction->m_oName = acTxt_;
							poAction->m_uiIndex = m_oArrAction.GetSize();
							m_oArrAction.Append( poAction );
						}
						else if( !strcmp( pcName, "anim" ) )
						{
							STRING_COPY( acTxt_, sizeof(acTxt_), poAttrib->Value() );
							LOG( "%s: %s\n", poAttrib->Name(), acTxt_ );
							
							CStr oIdxSeq( acTxt_ );
							if( oIdxSeq.GetSize() && poAction )
							{
								static const char cDelim_ = ',';
								
								unsigned int i = 0;
								while( true )
								{
									int iIdx;
									if( SSCANF( oIdxSeq.GetData() + i, "%d", &iIdx ) == 1 )
									{
										LOG( "index: %d\n", iIdx );
										poAction->AppendAnimIndex( iIdx );
									}
									const int c = oIdxSeq.Find( i, cDelim_ );
									if( c < 0 )
										break;
									i = c + 1;
								}
								
							}
						}
						else if( !strcmp( pcName, "sound" ) )
						{
							STRING_COPY( acTxt_, sizeof(acTxt_), poAttrib->Value() );
							LOG( "%s: %s\n", poAttrib->Name(), acTxt_ );
							
							TWav * poWav = m_poResMan_->NewWav( acTxt_ );
							if( poWav )
							{
								poAction->SetSoundStart( poWav );
							}
						}
						poAttrib = poAttrib->Next();
					}

					poAction->Init();
				}
			}
			/*
			else if( !strcmp( pcName, "joint_tracker" ) )
			{
				LOG( "joint_tracker:\n" );
				
				TiXmlElement * poElement = poParent->ToElement();
				if( poElement )
				{
					CJointTracker *poJointTracker = 0;
					
					TiXmlAttribute* poAttrib = poElement->FirstAttribute();
					while( poAttrib )
					{
						const char *pcName = poAttrib->Name();
						if( !strcmp( pcName, "name" ) )
						{
							STRING_COPY( acTxt_, sizeof(acTxt_), poAttrib->Value() );
							LOG( "%s: %s\n", poAttrib->Name(), acTxt_ );
							
							poJointTracker = GetJointTracker( acTxt_ );
							if( !poJointTracker )
							{
								poJointTracker = new CJointTracker;
								poJointTracker->m_oName = acTxt_;
								m_oLstJointTracker.Append( poJointTracker );
							}
						}
						else if( !strcmp( pcName, "joint" ) && poJointTracker )
						{
							STRING_COPY( acTxt_, sizeof(acTxt_), poAttrib->Value() );
							LOG( "%s: %s\n", poAttrib->Name(), acTxt_ );
							
							const int iJoint = m_poModel->GetJointIndex( acTxt_ );
							if( iJoint >= 0 )
								poJointTracker->New( iJoint );
						}
						poAttrib = poAttrib->Next();
					}
				}
			}
			*/
		}
	}
	break;
	case TiXmlNode::COMMENT:
		//LOG( "XML: Comment: [%s]", poParent->Value());
	break;
	case TiXmlNode::UNKNOWN:
		//LOG( "XML: Unknown" );
	break;
	case TiXmlNode::TEXT:
		//LOG( "XML: Text: [%s]", poParent->ToText()->Value() );
	break;
	case TiXmlNode::DECLARATION:
		//LOG( "XML: Declaration" );
	break;
	default:
	break;
	}
	LOG( "\n" );
	
	++uiCounter;
	
	for( TiXmlNode* poChild = poParent->FirstChild(); poChild != 0; poChild = poChild->NextSibling() ) 
	{
		ReadXML( poChild, uiCounter );
	}
	
	// Ganz am Schluss...
	if( uiCounter == 1 )
	{
	}
	return true;
}