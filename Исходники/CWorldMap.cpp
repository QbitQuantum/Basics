CPointMap CWorld::FindTypeNear_Top( const CPointMap & pt, IT_TYPE iType, int iDistance )
{
	ADDTOCALLSTACK("CWorld::FindTypeNear_Top");
#define RESOURCE_Z_CHECK 8
	CPointMap ptFound;
	CItemBase * pItemDef = NULL;
	CItem * pItem = NULL;
	CItemBaseDupe * pDupeDef = NULL;
	height_t Height = 0;
	BYTE z = 0;
	CPointMap ptTest;

	unsigned int iRetElem = 4;

	CPointMap ptElem[5];
	memset(ptElem, 0, sizeof(ptElem));
	//for ( iQty = 0; iQty < 4; ++iQty )
	//	ptElem[iQty].m_z = UO_SIZE_MIN_Z;
	ptElem[0].m_z = ptElem[1].m_z  = ptElem[2].m_z  = ptElem[3].m_z = UO_SIZE_MIN_Z;
	ptElem[4] = CPointMap(USHRT_MAX, USHRT_MAX, UO_SIZE_MIN_Z);

	bool fElem[4] = { false, false, false, false };

	// Check dynamics
	CWorldSearch Area( pt, iDistance );
	Area.SetAllShow( true );
	for (;;)
	{
		z = 0;
		Height = 0;
		pItem = Area.GetItem();
		if ( pItem == NULL )
			break;

		if ( pt.GetDist( pItem->GetTopPoint() ) > iDistance )
			continue;

		pItemDef = CItemBase::FindItemBase( pItem->GetDispID() );
		if ( pItemDef == NULL )
			continue;

		Height = pItemDef->GetHeight();
		if ( pItemDef->GetID() != pItem->GetDispID() ) //not a parent item
		{
			pDupeDef = CItemBaseDupe::GetDupeRef(static_cast<ITEMID_TYPE>(pItem->GetDispID()));
			if ( ! pDupeDef )
			{
				g_Log.EventDebug("Failed to get non-parent reference (dynamic) (DispID 0%x) (X: %d Y: %d Z: %d)\n",pItem->GetDispID(),ptTest.m_x,ptTest.m_y,ptTest.m_z);
				Height = pItemDef->GetHeight();
			}
			else
				Height = pDupeDef->GetHeight();
		}
		z = minimum( Height + pItem->GetTopPoint().m_z, UO_SIZE_Z ); //height + current position = the top point

		if ( ptElem[0].m_z > z ) //if ( ptElem[0].m_z > pItem->GetTopPoint().m_z )
			continue;

		if ( ((( z - pt.m_z ) > 0) && ( z - pt.m_z ) > RESOURCE_Z_CHECK ) || ((( pt.m_z - z ) < 0) && (( pt.m_z - z ) < - RESOURCE_Z_CHECK ))) //if ( ((( pItem->GetTopPoint().m_z - pt.m_z ) > 0) && ( pItem->GetTopPoint().m_z - pt.m_z ) > RESOURCE_Z_CHECK ) || ((( pt.m_z - pItem->GetTopPoint().m_z ) < 0) && (( pt.m_z - pItem->GetTopPoint().m_z ) < - RESOURCE_Z_CHECK )))
			continue;

		if (( z < ptElem[0].m_z ) || (( z == ptElem[0].m_z ) && ( fElem[0] )))
			continue;
        
		ptElem[0] = pItem->GetTopPoint();
		ptElem[0].m_z = z;
		fElem[0] = false;

		//DEBUG_ERR(("dynamic pItem->IsType( iType %d) %d\n",iType,pItem->IsType( iType )));
		if ( pItem->IsType( iType ) )  //( pItem->Item_GetDef()->IsType(iType) ) )
		{
			fElem[0] = true;
			iRetElem = 0;
		}
	}

	// Parts of multis ?
	const CGrayMulti * pMulti 			= NULL;		// Multi Def (multi check)
	const CUOMultiItemRec2 * pMultiItem = NULL;		// Multi item iterator
	CRegionBase * pRegion				= NULL;
	CRegionLinks rlinks;
	size_t iRegionQty = pt.GetRegions( REGION_TYPE_MULTI, rlinks );
	if ( iRegionQty > 0 )
	{
		for ( size_t iRegion = 0; iRegion < iRegionQty; pMulti = NULL, ++iRegion)
		{
			pRegion = rlinks.GetAt(iRegion);
			pItem = pRegion->GetResourceID().ItemFind();
			if ( !pItem )
				continue;
			pMulti = g_Cfg.GetMultiItemDefs(pItem);
			if ( !pMulti )
				continue;
			size_t iMultiQty = pMulti->GetItemCount();
			for ( size_t iMulti = 0; iMulti < iMultiQty; pItemDef = NULL, pMultiItem = NULL, Height = 0, ++iMulti )
			{
				pMultiItem = pMulti->GetItem(iMulti);
				
				if ( !pMultiItem )
					break;

				//DEBUG_ERR(("abs( pMultiItem->m_dx ) %x, abs( pMultiItem->m_dy ) %x, abs( pMultiItem->m_dz ) %x,\n             iDistance %x IF STATEMENT %x %x\n", abs( pMultiItem->m_dx ), abs( pMultiItem->m_dy ), abs( pMultiItem->m_dz ), iDistance, ( abs( pMultiItem->m_dx ) <= iDistance ), ( abs( pMultiItem->m_dy ) <= iDistance ) ));

				if ( !pMultiItem->m_visible )
					continue;

				ptTest = CPointMap( pMultiItem->m_dx + pt.m_x, pMultiItem->m_dy + pt.m_y, static_cast<signed char>( pMultiItem->m_dz + pt.m_z ), pt.m_map );

				pItemDef = CItemBase::FindItemBase( pMultiItem->GetDispID() );
				if ( pItemDef == NULL )
					continue;

				Height = pItemDef->GetHeight();
				if ( pItemDef->GetID() != pMultiItem->GetDispID() ) //not a parent item
				{
					pDupeDef = CItemBaseDupe::GetDupeRef(static_cast<ITEMID_TYPE>(pMultiItem->GetDispID()));
					if ( ! pDupeDef )
					{
						g_Log.EventDebug("Failed to get non-parent reference (multi) (DispID 0%x) (X: %d Y: %d Z: %d)\n",pMultiItem->GetDispID(),ptTest.m_x,ptTest.m_y,ptTest.m_z);
						Height = pItemDef->GetHeight();
					}
					else
						Height = pDupeDef->GetHeight();
				}
				ptTest.m_z = minimum(ptTest.m_z + Height, UO_SIZE_Z); //height + current position = the top point

				if ( pt.GetDist( ptTest ) > iDistance )
					continue;

				if ( ptElem[1].m_z > ptTest.m_z )
					continue;
		
				if ( ((( ptTest.m_z - pt.m_z ) > 0) && ( ptTest.m_z - pt.m_z ) > RESOURCE_Z_CHECK ) || ((( pt.m_z - ptTest.m_z ) < 0) && (( pt.m_z - ptTest.m_z ) < - RESOURCE_Z_CHECK )))
					continue;
	
				if (( ptTest.m_z < ptElem[1].m_z ) || (( ptTest.m_z == ptElem[1].m_z ) && ( fElem[1] )))
					continue;
		        //DEBUG_ERR(("pMultiItem->GetDispID()%x\n",pMultiItem->GetDispID()));
				ptElem[1] = ptTest;
				fElem[1] = false;

				//DEBUG_ERR(("multi pItemDef->IsType( iType %d) %d\n",iType,pItemDef->IsType( iType )));
				if ( pItemDef->IsType( iType ) )
				{
					fElem[1] = true;
					//if ( ptElem[iRetElem].m_z > ptElem[1].m_z )
					if ( ptElem[1].m_z > ptElem[iRetElem].m_z )
						iRetElem = 1;
				}

				//DEBUG_ERR(( "DISPID: %x X %d Y %d Z %d\n", pMultiItem->GetDispID(), (pMultiItem->m_dx), (pMultiItem->m_dy), (pMultiItem->m_dz) ));
			}
		}
	}

	// STATIC - checks one 8x8 block
	const CGrayMapBlock * pMapBlock = GetMapBlock( pt );
	ASSERT( pMapBlock );

	size_t iStaticQty = pMapBlock->m_Statics.GetStaticQty();
	if ( iStaticQty > 0 )  // no static items here.
	{
		const CUOStaticItemRec * pStatic = NULL;

		for ( size_t i = 0; i < iStaticQty; ++i, pStatic = NULL, Height = 0, pItemDef = NULL )
		{
			pStatic = pMapBlock->m_Statics.GetStatic( i );

			ptTest = CPointMap( pStatic->m_x + pMapBlock->m_x, pStatic->m_y + pMapBlock->m_y, pStatic->m_z, pt.m_map );

			pItemDef = CItemBase::FindItemBase( pStatic->GetDispID() );
			if ( pItemDef == NULL )
				continue;

			//DEBUG_ERR(("pStatic->GetDispID() %d; name %s; pStatic->m_z %d\n",pStatic->GetDispID(),pItemDef->GetName(),pStatic->m_z));
			Height = pItemDef->GetHeight();
			if ( pItemDef->GetID() != pStatic->GetDispID() ) //not a parent item
			{
				pDupeDef = CItemBaseDupe::GetDupeRef(static_cast<ITEMID_TYPE>(pStatic->GetDispID()));
				if ( ! pDupeDef )
				{
					g_Log.EventDebug("Failed to get non-parent reference (static) (DispID 0%x) (X: %d Y: %d Z: %d)\n",pStatic->GetDispID(),ptTest.m_x,ptTest.m_y,ptTest.m_z);
					Height = pItemDef->GetHeight();
				}
				else
					Height = pDupeDef->GetHeight();
			}
			ptTest.m_z = minimum(ptTest.m_z + Height, UO_SIZE_Z); //height + current position = the top point

			if ( pt.GetDist( ptTest ) > iDistance )
				continue;

			if ( pt.GetDist( ptTest ) > iDistance )
				continue;

			//if ( ptElem[2].m_z > pStatic->m_z )
			if ( ptElem[2].m_z > ptTest.m_z )
				continue;

			if ( ((( pStatic->m_z - pt.m_z ) > 0) && ( pStatic->m_z - pt.m_z ) > RESOURCE_Z_CHECK ) || ((( pt.m_z - pStatic->m_z ) < 0) && (( pt.m_z - pStatic->m_z ) < - RESOURCE_Z_CHECK )))
				continue;

			if (( ptTest.m_z < ptElem[2].m_z ) || (( ptTest.m_z == ptElem[2].m_z ) && ( fElem[2] )))
				continue;

			ptElem[2] = ptTest;
			fElem[2] = false;

			//DEBUG_ERR(("static pItemDef->IsType( iType %d) %d;pItemDef->GetType() %d;pItemDef->GetID() %d;pItemDef->GetDispID() %d\n",iType,pItemDef->IsType( iType ),pItemDef->GetType(),pItemDef->GetID(),pItemDef->GetDispID()));
			if ( pItemDef->IsType( iType ) )
			{
				//DEBUG_ERR(("found %d; ptTest: %d,%d,%d\n",__LINE__,ptTest.m_x,ptTest.m_y,ptTest.m_z));
				fElem[2] = true;
				//DEBUG_ERR(("ptElem[iRetElem].m_z %d, ptElem[2].m_z %d\n",ptElem[iRetElem].m_z,ptElem[2].m_z));
				//if ( ptElem[iRetElem].m_z > ptElem[2].m_z )
				if ( ptElem[2].m_z > ptElem[iRetElem].m_z )
					iRetElem = 2;
			}
		}
	}

	// Check for appropriate terrain type
	CRectMap rect;
	rect.SetRect( pt.m_x - iDistance, pt.m_y - iDistance,
		pt.m_x + iDistance + 1, pt.m_y + iDistance + 1,
		pt.m_map);

	const CUOMapMeter * pMeter = NULL;
	for ( int x = rect.m_left; x < rect.m_right; ++x, pMeter = NULL )
	{
		for ( int y = rect.m_top; y < rect.m_bottom; ++y, pMeter = NULL )
		{
			ptTest = CPointMap(static_cast<WORD>(x), static_cast<WORD>(y), pt.m_z, pt.m_map);
			pMeter = GetMapMeter(ptTest);
			if ( !pMeter )
				continue;
			if ( pt.GetDist( ptTest ) > iDistance )
				continue;
			if ( ptElem[3].m_z > pMeter->m_z )
				continue;

			//DEBUG_ERR(("(( pMeter->m_z (%d) - pt.m_z (%d) ) > 0) && ( pMeter->m_z (%d) - pt.m_z (%d) ) > RESOURCE_Z_CHECK (%d) >> %d\n",pMeter->m_z,pt.m_z,pMeter->m_z,pt.m_z,RESOURCE_Z_CHECK,(( pMeter->m_z - pt.m_z ) > 0) && ( pMeter->m_z - pt.m_z ) > RESOURCE_Z_CHECK));
			//DEBUG_ERR(("(( pt.m_z (%d) - pMeter->m_z (%d) ) < 0) && (( pt.m_z (%d) - pMeter->m_z (%d) ) < - RESOURCE_Z_CHECK (%d) )) >> %d\n",pt.m_z,pMeter->m_z,pt.m_z,pMeter->m_z,- RESOURCE_Z_CHECK,((( pt.m_z - pMeter->m_z ) < 0) && (( pt.m_z - pMeter->m_z ) < - RESOURCE_Z_CHECK ))));
			if ( ((( pMeter->m_z - pt.m_z ) > 0) && ( pMeter->m_z - pt.m_z ) > RESOURCE_Z_CHECK ) || ((( pt.m_z - pMeter->m_z ) < 0) && (( pt.m_z - pMeter->m_z ) < - RESOURCE_Z_CHECK )))
				continue;

			//DEBUG_ERR(("pMeter->m_z (%d) < ptElem[3].m_z (%d) >> %d\n",pMeter->m_z,ptElem[3].m_z,pMeter->m_z < ptElem[3].m_z));
			if (( pMeter->m_z < ptElem[3].m_z ) || (( pMeter->m_z == ptElem[3].m_z ) && ( fElem[3] )))
				continue;

			ptElem[3] = ptTest;
			fElem[3] = false;

			//DEBUG_ERR(("iType %x, TerrainType %x\n",iType,g_World.GetTerrainItemType( pMeter->m_wTerrainIndex )));
			if ( iType == g_World.GetTerrainItemType( pMeter->m_wTerrainIndex ) )
			{
				fElem[3] = true;
				//if ( ptElem[iRetElem].m_z > ptElem[3].m_z )
				//DEBUG_ERR(("ptElem[3].m_z %d; ptElem[iRetElem].m_z %d\n",ptElem[3].m_z, ptElem[iRetElem].m_z));
				if ( ptElem[3].m_z > ptElem[iRetElem].m_z )
						iRetElem = 3;
				//DEBUG_ERR(("fElem3 %d %d\n",ptElem[3].m_z, fElem[3]));
				continue;
			}

			rect.SetRect( pt.m_x - iDistance, pt.m_y - iDistance, pt.m_x + iDistance + 1, pt.m_y + iDistance + 1, pt.m_map);
		}
	}

	/*CPointMap a;
	a.m_z = maximum(
	// priority dynamic->multi->static->terrain
	int iRetElem;
	if (( ptElem[0].m_z >= ptElem[1].m_z ) && ( fElem[0] ))
		iRetElem = 0;
	else if (( ptElem[1].m_z >= ptElem[2].m_z ) && ( fElem[1] ))
		iRetElem = 1;
	else if (( ptElem[2].m_z >= ptElem[3].m_z ) && ( fElem[2] ))
		iRetElem = 2;
	else if ( fElem[3] )
		iRetElem = 3;
	else
		iRetElem = 4;*/

	ASSERT(iRetElem < COUNTOF(ptElem));
	if ( 0 != iRetElem && ptElem[0].m_z > ptElem[iRetElem].m_z )
			 iRetElem = 4;
	else if ( 1 != iRetElem && ptElem[1].m_z > ptElem[iRetElem].m_z )
		     iRetElem = 4;
	else if ( 2 != iRetElem && ptElem[2].m_z > ptElem[iRetElem].m_z )
		     iRetElem = 4;
	else if ( 3 != iRetElem && ptElem[3].m_z > ptElem[iRetElem].m_z )
		     iRetElem = 4;

	//DEBUG_ERR(("iRetElem %d; %d %d %d %d; %d %d %d ISVALID: %d\n",iRetElem,ptElem[1].m_z,ptElem[2].m_z,ptElem[3].m_z,ptElem[4].m_z,pt.m_x,pt.m_y,pt.m_z,ptElem[iRetElem].IsValidPoint()));
	//DEBUG_ERR(("X: %d  Y: %d  Z: %d\n",ptElem[iRetElem].m_x,ptElem[iRetElem].m_y,ptElem[iRetElem].m_z));
	return ( ptElem[iRetElem] );
#undef RESOURCE_Z_CHECK
}