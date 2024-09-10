BOOL CVCAMetaParserMSXML::ParseObjects( )
{
	// Find all the objects
	CComBSTR					bsTag;
	

	MSXML2::IXMLDOMNodePtr		pNode, pSubNode, pSubSubNode, pSubSubSubNode;	// Great names eh ;~)
	MSXML2::IXMLDOMNodeListPtr	pNodeList, pSubNodeList;

	// See if we have any objects this time round
	bsTag = CComBSTR( _XML_VCA ) += CComBSTR("/") += CComBSTR( _XML_OBJECTS );

	pNode = m_pDOMDoc->selectSingleNode( bsTag.operator BSTR() );
// 	ATLTRACE( "====================================================== \n" );

	if( pNode )
	{
		// There are some in this packet
		// Wipe out all exisiting
		m_vcaObjects.ulTotalObject = 0;

		// Select all objects
		bsTag = CComBSTR( _XML_OBJECT );

		pNodeList = pNode->selectNodes( bsTag.operator BSTR() );

		// Iterate through all the nodes
		pNode = pNodeList->nextNode();

		while( pNode )
		{
			VCA5_PACKET_OBJECT	vcaObj;
			memset( &vcaObj, 0, sizeof( vcaObj ) );

			// Id
			bsTag = CComBSTR( _XML_ID );
			pSubNode = pNode->selectSingleNode( bsTag.operator BSTR() );
			if( pSubNode )
			{
				VarUI4FromStr( pSubNode->text, LCID_ENGLISH, LOCALE_NOUSEROVERRIDE, (unsigned long *)&vcaObj.ulId );
			}

			// Calibrated height and speed
			bsTag = CComBSTR( _XML_CH );
			pSubNode = pNode->selectSingleNode( bsTag.operator BSTR() );
			if( pSubNode )
			{				
				VarUI4FromStr( pSubNode->text, LCID_ENGLISH, LOCALE_NOUSEROVERRIDE, (unsigned long *)&vcaObj.ulCalibHeight);
			}

			bsTag = CComBSTR( _XML_CS );
			pSubNode = pNode->selectSingleNode( bsTag.operator BSTR() );
			if( pSubNode )
			{
				VarUI4FromStr( pSubNode->text, LCID_ENGLISH, LOCALE_NOUSEROVERRIDE, (unsigned long *)&vcaObj.ulCalibSpeed);
			}

			bsTag = CComBSTR( _XML_CA );
			pSubNode = pNode->selectSingleNode( bsTag.operator BSTR() );
			if( pSubNode )
			{
				VarUI4FromStr( pSubNode->text, LCID_ENGLISH, LOCALE_NOUSEROVERRIDE, (unsigned long *)&vcaObj.ulCalibArea);
			}

			bsTag = CComBSTR( _XML_CLS );
			pSubNode = pNode->selectSingleNode( bsTag.operator BSTR() );
			if( pSubNode )
			{
				VarI4FromStr( pSubNode->text, LCID_ENGLISH, LOCALE_NOUSEROVERRIDE, (long *)&vcaObj.iClassificationId);
			}
			else
			{
				vcaObj.iClassificationId = -2;  // unknown	
			}

			bsTag = CComBSTR( _XML_COLSIG );
			pSubNode = pNode->selectSingleNode( bsTag.operator BSTR() );
			if( pSubNode )
			{
				std::string tempColSigs = pSubNode->text;
				for(int n=0; n<VCA5_APP_PALETTE_SIZE; n++)
				{
					vcaObj.colSigs[n] = (UCHAR)strtoul( tempColSigs.substr(n*2,2).c_str(), NULL, 16 );
				}

// 				ATLTRACE( "%s: %d %d %d %d %d %d %d %d %d %d \n",  tempColSigs.c_str(), 
// 					vcaObj.colSigs[0], vcaObj.colSigs[1], vcaObj.colSigs[2], vcaObj.colSigs[3], vcaObj.colSigs[4],
// 					vcaObj.colSigs[5], vcaObj.colSigs[6], vcaObj.colSigs[7], vcaObj.colSigs[8], vcaObj.colSigs[9] );
			}
			else
			{
				for(int n=0; n<VCA5_APP_PALETTE_SIZE; n++)
				{
					vcaObj.colSigs[n] = 0;
				}
			}

			// Bounding box
			ParseBBox( pNode, &vcaObj.bBox );


			// Trail
			bsTag = CComBSTR( _XML_TRAIL );
			pSubNode = pNode->selectSingleNode( bsTag.operator BSTR() );

			if( pSubNode )
			{
				bsTag = CComBSTR( _XML_PT );
				pSubNodeList = pSubNode->selectNodes( bsTag.operator BSTR() );

				pSubSubNode = pSubNodeList->nextNode();
				vcaObj.trail.usNumTrailPoints = 0;
				while( pSubSubNode )
				{
					VCA5_POINT	vcaPoint;
					memset( &vcaPoint, 0, sizeof( vcaPoint ) );

					bsTag = CComBSTR( _XML_X );
					pSubSubSubNode = pSubSubNode->selectSingleNode( bsTag.operator BSTR() );
					if( pSubSubSubNode )
					{
						VarUI2FromStr( pSubSubSubNode->text, LCID_ENGLISH, LOCALE_NOUSEROVERRIDE, (unsigned short *)&vcaPoint.x );
					}

					bsTag = CComBSTR( _XML_Y );
					pSubSubSubNode = pSubSubNode->selectSingleNode( bsTag.operator BSTR() );
					if( pSubSubSubNode )
					{
						VarUI2FromStr( pSubSubSubNode->text, LCID_ENGLISH, LOCALE_NOUSEROVERRIDE, (unsigned short *)&vcaPoint.y);
					}

					// Ph it (like Salt 'n' Pepa)
					vcaObj.trail.trailPoints[vcaObj.trail.usNumTrailPoints] = vcaPoint;
					vcaObj.trail.usNumTrailPoints++;	

					pSubSubNode = pSubNodeList->nextNode();
				}
			}

			// Flags
			bsTag = CComBSTR( _XML_FLAGS );
			pSubNode = pNode->selectSingleNode( bsTag.operator BSTR() );
			if( pSubNode )
			{
				VarUI4FromStr( pSubNode->text, LCID_ENGLISH, LOCALE_NOUSEROVERRIDE, (unsigned long *)&vcaObj.ulFlags );
			}


			m_vcaObjects.Objects[m_vcaObjects.ulTotalObject]  = vcaObj;
			//m_vcaObjects.ph_back( vcaObj );
			m_vcaObjects.ulTotalObject++;

			pNode = pNodeList->nextNode();
		}
	}

	return TRUE;
}