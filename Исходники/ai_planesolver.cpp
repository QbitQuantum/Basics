float CAI_PlaneSolver::AdjustRegulationWeight( CBaseEntity *pEntity, float weight )
{
	if ( pEntity->MyNPCPointer() != NULL )
	{
		// @TODO (toml 10-03-02): How to do this with non-NPC entities. Should be using intended solve velocity...
		Vector2D velOwner = GetNpc()->GetMotor()->GetCurVel().AsVector2D();
		Vector2D velBlocker = ((CAI_BaseNPC *)pEntity)->GetMotor()->GetCurVel().AsVector2D();

		Vector2D velOwnerNorm = velOwner;
		Vector2D velBlockerNorm = velBlocker;

		float speedOwner   = Vector2DNormalize( velOwnerNorm );
		float speedBlocker = Vector2DNormalize( velBlockerNorm );

		float dot = velOwnerNorm.Dot( velBlockerNorm );

		if ( speedBlocker > 0 )
		{
			if ( dot > 0 && speedBlocker >= speedOwner * 0.9 )
			{
				if ( dot > 0.86 )
				{
					// @Note (toml 10-10-02): Even in the case of no obstacle, we generate
					// a suggestion in because we still want to continue sweeping the
					// search
					weight = 0;
				}
				else if ( dot > 0.7 )
				{
					weight *= sq( weight );
				}
				else 
					weight *= weight;
			}
		}
	}

	return weight;
}