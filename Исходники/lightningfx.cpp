void CLightningFX::EmitBolts( float tmFrameTime )
{
	// Make sure enough time between emissions has passed...
	m_tmElapsedEmission += tmFrameTime;

	if( m_fDelay < m_tmElapsedEmission )
	{
		LTransform		lTrans;
		LTVector		vAttractorPos;
		ILTModel		*pModelLT = m_pLTClient->GetModelLT();

		uint32	nActiveBolts = GetRandom( (int)GetProps()->m_nMinNumBolts, (int)GetProps()->m_nMaxNumBolts );
		uint32	nBolt;

		bool	bCanUseAttractors = (m_lstAttractors.size() > 0);
		bool	bCanUseRadius = (GetProps()->m_fOmniDirectionalRadius >= 1.0f);

		CLightningBolt *pBolt = LTNULL;
		LightningBolts::iterator iter;

		for( nBolt = 0, iter = m_lstBolts.begin(); iter != m_lstBolts.end(), nBolt < nActiveBolts; ++iter, ++nBolt )
		{
			pBolt = *iter;
			
			pBolt->m_fWidth = GetRandom( GetProps()->m_fMinBoltWidth, GetProps()->m_fMaxBoltWidth );
			pBolt->m_fLifetime = GetRandom( GetProps()->m_fMinLifetime, GetProps()->m_fMaxLifetime );
			pBolt->m_tmElapsed = 0.0f;
			pBolt->m_bActive = true;
			
			// Grab the position of the object to compensate for offset
		
			if( m_hTarget )
			{
				m_pLTClient->GetObjectPos( m_hTarget, &vAttractorPos );
			}
			else
			{
				vAttractorPos = m_vTargetPos;
			}

			// Decide if we should use an attractor or radius for the end pos...
			
			if( bCanUseAttractors && (!bCanUseRadius || GetRandom(0,1)) )
			{
				uint8	nIndex = GetRandom( 0, (int)(m_lstAttractors.size()) - 1 );
				CAttractor cAttractor = m_lstAttractors[nIndex];

				if( cAttractor.GetTransform( lTrans, true ) == LT_OK )
				{
					vAttractorPos = lTrans.m_Pos;
				}
			}	
			else if( bCanUseRadius )
			{
				LTVector vRandomPos;
				vRandomPos.x = GetRandom( -1.0f, 1.0f );
				vRandomPos.y = GetRandom( -1.0f, 1.0f );
				vRandomPos.z = GetRandom( -1.0f, 1.0f );
				
				vRandomPos.Normalize();
				vRandomPos *= GetRandom( -GetProps()->m_fOmniDirectionalRadius, GetProps()->m_fOmniDirectionalRadius );

				vAttractorPos = m_vPos + vRandomPos;

				IntersectQuery	iQuery;
				IntersectInfo	iInfo;

				iQuery.m_From	= m_vPos;
				iQuery.m_To		= vAttractorPos;

				if( m_pLTClient->IntersectSegment( &iQuery, &iInfo ))
				{
					vAttractorPos = iInfo.m_Point;
				}
			}

			
			LTVector vNew = m_vPos;
			LTVector vDir = vAttractorPos - vNew;
						
			float fStep = vDir.Length() / (float)pBolt->m_nNumSegments;
			float fPerturb = GetRandom( GetProps()->m_fMinPerturb, GetProps()->m_fMaxPerturb );
			
			vDir.Normalize();
			LTRotation rRot = LTRotation( vDir, LTVector( 0.0f, 1.0f, 0.0f ));
				
			CLinkListNode<PT_TRAIL_SECTION> *pNode = pBolt->m_collPathPts.GetHead();
			while( pNode )
			{
				pNode->m_Data.m_vPos = vNew;
				pNode->m_Data.m_tmElapsed = 0.0f;
				pNode->m_Data.m_vBisector.Init();
												
				// Add in some perturb going in the direction of the attractor pos for the next section...
				
				vNew +=	(rRot.Forward() * fStep );
				vNew += (rRot.Up() * GetRandom( -fPerturb, fPerturb ));
				vNew += (rRot.Right() * GetRandom( -fPerturb, fPerturb ));

				// Make sure the last section goes to the end pos...

				if( !pNode->m_pNext )
					pNode->m_Data.m_vPos = vAttractorPos;

				pNode = pNode->m_pNext;
			}
		}

		// Decide when the next emission will be...

		m_tmElapsedEmission = 0.0f;
		m_fDelay = GetRandom( GetProps()->m_fMinDelay, GetProps()->m_fMaxDelay );
	}
}