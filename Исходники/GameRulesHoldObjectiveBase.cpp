//------------------------------------------------------------------------
void CGameRulesHoldObjectiveBase::UpdateEffect(float frameTime)
{
	IEntity *pRingEntity = gEnv->pEntitySystem->GetEntity(m_effectData.ringEntityID);
	
	if(pRingEntity)
	{
		// Update lerps
		m_effectData.materialColorLerp.UpdateLerp(frameTime);
		m_effectData.particleColorLerp.UpdateLerp(frameTime);

		// Update ring cgf
		if(m_effectData.alphaLerp.HasFinishedLerping() == false)
		{
			if(m_effectData.alphaFadeInDelay > 0.0f)
			{
				m_effectData.alphaFadeInDelay -= frameTime;
				if(m_effectData.alphaFadeInDelay <= 0.0f)
				{
					m_effectData.alphaFadeInDelay = 0.0f;
					float alpha = min(m_effectData.alphaLerp.GetValue(),0.99f);
					SetRingAlpha(pRingEntity,alpha);
					pRingEntity->Hide(false);
				}
			}
			else
			{
				m_effectData.alphaLerp.UpdateLerp(frameTime);
				float alpha = min(m_effectData.alphaLerp.GetValue(),0.99f);
				SetRingAlpha(pRingEntity,alpha);
				
				// Fully faded out, so hide
				if(m_effectData.alphaLerp.HasFinishedLerping() && m_effectData.alphaLerp.GetNewValue() == 0.0f)
				{
					pRingEntity->Hide(true);
					SetNewEffectColor(eRPT_Neutral);
				}
			}
		}

		// Update Color
		float lerpValue = m_effectData.materialColorLerp.GetValue();
		Vec3 currentColor = LERP(*m_effectData.pPrevCol,*m_effectData.pDestCol,lerpValue);

		// Set ring color
		IEntityRenderProxy* pRenderProxy = (IEntityRenderProxy*)pRingEntity->GetProxy(ENTITY_PROXY_RENDER);
		if(pRenderProxy)
		{
			IMaterial* pRingMaterial = pRenderProxy->GetRenderMaterial();
			SetMaterialDiffuseColor(pRingMaterial,currentColor);
		}
		
		// Set particle geom material color
		SetMaterialDiffuseColor(m_effectData.pParticleGeomMaterial,currentColor);
	}
}