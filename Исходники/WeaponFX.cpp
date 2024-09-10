void CWeaponFX::PlayBulletFlyBySound()
{
	if (!m_pWeapon || !m_pAmmo) return;

	if (m_pAmmo->eType != VECTOR) return;

	// Camera pos

	HOBJECT hCamera = g_pGameClientShell->GetCamera();
    LTVector vPos;
    g_pLTClient->GetObjectPos(hCamera, &vPos);

	// We only play the flyby sound if we won't hear an impact or
	// fire sound...

	LTVector vDist = m_vFirePos - vPos;
	if (vDist.Mag() < m_pWeapon->nFireSoundRadius) return;

	if (m_pAmmo->pImpactFX)
	{
		vDist = m_vPos - vPos;
		if (vDist.Mag() < m_pAmmo->pImpactFX->nSoundRadius) return;
	}


	// See if the camera is close enough to the bullet path to hear the
	// bullet...

	LTFLOAT fRadius = g_cvarFlyByRadius.GetFloat();

	LTVector vDir = m_vDir;

	const LTVector vRelativePos = vPos - m_vFirePos;
    const LTFLOAT fRayDist = vDir.Dot(vRelativePos);
	LTVector vBulletDir = (vDir*fRayDist - vRelativePos);

    const LTFLOAT fDistSqr = vBulletDir.MagSqr();

	if (fDistSqr < fRadius*fRadius)
	{
		vPos += vBulletDir;
		g_pClientSoundMgr->PlaySoundFromPos(vPos, "Guns\\Snd\\flyby.wav",
			g_cvarFlyBySoundRadius.GetFloat(), SOUNDPRIORITY_MISC_LOW);
	}
}