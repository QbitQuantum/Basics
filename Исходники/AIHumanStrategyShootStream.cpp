//----------------------------------------------------------------------------
//              
//	ROUTINE:	CAIHumanStrategyShootStream::UpdateAiming()
//              
//	PURPOSE:	
//              
//----------------------------------------------------------------------------
/*virtual*/ void CAIHumanStrategyShootStream::UpdateAiming(HOBJECT hTarget)
{
	if ( m_flStreamTime < g_pLTServer->GetTime() )
	{
		// Don't calculate new stream time until finished firing animation.
		if( !GetAnimationContext()->IsLocked() )
		{
			CalculateStreamTime();
		}

		Aim();
	}
	else
	{
		// We're done waiting, fire if we're at a reasonable angle

		if ( m_bIgnoreFOV )
		{
			Fire();
		}
		else
		{
			LTVector vTargetPos;
			g_pLTServer->GetObjectPos(hTarget, &vTargetPos);

			LTVector vDir = vTargetPos - GetAI()->GetPosition();
			vDir.y = 0.0f;
			vDir.Normalize();

			if ( vDir.Dot(GetAI()->GetTorsoForward()) < 0.70f )
			{
				Aim();
			}
			else
			{
				Fire();
			}
		}
	}
}