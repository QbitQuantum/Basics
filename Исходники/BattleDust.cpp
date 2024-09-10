void CBattleDust::UpdateParticlesForArea(CBattleEvent* pEvent)
{
	float oldParticleCount = pEvent->m_numParticles;
	float fraction = CLAMP((pEvent->m_radius - m_entitySpawnPower) / (m_maxEventPower - m_entitySpawnPower), 0.0f, 1.0f);
	pEvent->m_numParticles = LERP(m_minParticleCount, m_maxParticleCount, fraction);

	if(pEvent->GetGameObject() && oldParticleCount != pEvent->m_numParticles)
	{
		pEvent->GetGameObject()->ChangedNetworkState(CBattleEvent::PROPERTIES_ASPECT);
	}
}