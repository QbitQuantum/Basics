bool CClientFXMgr::CreateFXKey( CLIENTFX_INSTANCE* pInst, FX_KEY* pKey )
{
	if( !pInst || !pKey ) 
		return false;
	//
	// We need to go ahead and create this effect
	//

	assert(m_hCamera);

	FX_BASEDATA	fxData;
	fxData.m_vPos				= pInst->m_vPos;
	fxData.m_rRot				= pInst->m_rRot;
	fxData.m_dwID				= pInst->m_dwID;
	fxData.m_hTarget			= pInst->m_hTarget;
	fxData.m_dwObjectFlags		= pInst->m_dwObjectFlags;
	fxData.m_dwObjectFlags2		= pInst->m_dwObjectFlags2;
	fxData.m_bUseTargetData		= pInst->m_bUseTargetData;
	fxData.m_vTargetPos			= pInst->m_vTargetPos;
	fxData.m_vTargetNorm		= pInst->m_vTargetNorm;
	fxData.m_hCamera			= m_hCamera;

	// Save the parent
	fxData.m_hParent = pInst->m_hParent;

	// Is this FX supposed to be motion linked to another FX?
	if (pKey->m_bLinked)
	{
		CLinkListNode<FX_LINK>	*pNode = pInst->m_collActiveFX.GetHead();

		while (pNode)
		{
			if (pNode->m_Data.m_dwID == pKey->m_dwLinkedID)
			{
				// This is the one !!!
				if (pInst->ExistFX(pNode->m_Data.m_pFX))
				{
					CBaseFX	 *pMotionLinkFX	= pNode->m_Data.m_pFX;
					fxData.m_hParent = pMotionLinkFX->GetFXObject();
				}

				// done
				break;
			}
			
			pNode = pNode->m_pNext;
		}
	}

	// Create the FX
	CBaseFX *pNewFX = CreateFX(pKey->m_pFxRef->m_sName, &fxData, pKey->m_pProps, pInst->m_hParent);

	if( pNewFX )
	{
		pNewFX->SetVisible(false);
		pNewFX->ClearState(FS_INITIALFRAME | FS_ACTIVE | FS_SHUTTINGDOWN | FS_SUSPENDED);

		// Add it onto the list for link referencing

		FX_LINK	fxLink;
		fxLink.m_dwID = pKey->m_dwID;
		fxLink.m_pFX  = pNewFX;
		fxLink.m_pRef = pKey;

		pInst->m_collActiveFX.AddHead(fxLink);
	}
	else
	{
		return false;
	}

	return true;
}