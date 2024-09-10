void CScriptProxy::OnCollision(CEntity* pTarget, int matId, const Vec3 &pt, const Vec3 &n, const Vec3 &vel, const Vec3 &targetVel, int partId, float mass)
{
	if (!CurrentState()->IsStateFunctionImplemented(ScriptState_OnCollision))
		return;

	FUNCTION_PROFILER( GetISystem(), PROFILE_ENTITY );

	if (!m_hitTable)
		m_hitTable.Create(gEnv->pScriptSystem);
	{
		Vec3               dir(0, 0, 0);
		CScriptSetGetChain chain(m_hitTable);
		chain.SetValue("normal", n);
		chain.SetValue("pos", pt);

		if (vel.GetLengthSquared() > 1e-6f)
		{
			dir = vel.GetNormalized();
			chain.SetValue("dir", dir);
		}

		chain.SetValue("velocity", vel);
		chain.SetValue("target_velocity", targetVel);
		chain.SetValue("target_mass", mass);
		chain.SetValue("partid", partId);
		chain.SetValue("backface", n.Dot(dir) >= 0);
		chain.SetValue("materialId", matId);

		if (pTarget)
		{
			ScriptHandle sh;
			sh.n = pTarget->GetId();

			if (pTarget->GetPhysics())
			{
				chain.SetValue("target_type", (int)pTarget->GetPhysics()->GetType());
			}
			else
			{
				chain.SetToNull("target_type");
			}

			chain.SetValue("target_id", sh);

			if (pTarget->GetScriptTable())
			{
				chain.SetValue("target", pTarget->GetScriptTable());
			}
		}
		else
		{
			chain.SetToNull("target_type");
			chain.SetToNull("target_id");
			chain.SetToNull("target");
		}
	}

	m_pScript->CallStateFunction( CurrentState(),m_pThis,ScriptState_OnCollision, m_hitTable);
}