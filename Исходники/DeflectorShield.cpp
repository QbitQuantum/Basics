void CDeflectorShield::ShootDeflectedEnergy(const CDeflectorShield::SDeflectedEnergy& energy)
{
	if (!m_pAmmoClass)
		return;
	CProjectile* pEnergyBlast = g_pGame->GetWeaponSystem()->SpawnAmmo(m_pAmmoClass, false);
	if (!pEnergyBlast)
		return;

	const Matrix34& worldTransform = GetEntity()->GetWorldTM();

	const float positionBias = 0.05f;

	const Vec3 worldReflectPos = worldTransform.TransformPoint(energy.m_localPosition);
	const Vec3 worldReflectDir = worldTransform.TransformVector(energy.m_localDirection);

	const Vec3 worldSpreadU = worldReflectDir.GetOrthogonal();
	const Vec3 worldSpreadV = worldReflectDir.Cross(worldSpreadU);

	const float spreadOffset = cry_random(0.0f, m_spread);
	
	const Vec3 position = worldReflectPos + worldReflectDir * positionBias;
	Vec3 direction = 
		worldReflectDir + 
		(worldSpreadU * cry_random(0.0f, m_spread)) + 
		(worldSpreadV * cry_random(0.0f, m_spread));
	direction.Normalize();

	CProjectile::SProjectileDesc projectileDesc(
		0, 0, 0, energy.m_damage, m_dropMinDistance, m_dropPerMeter, float(m_minDamage), m_hitTypeId,
		0, false);
	pEnergyBlast->SetParams(projectileDesc);
	pEnergyBlast->Launch(position, direction, Vec3(ZERO));
}