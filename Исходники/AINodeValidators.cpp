bool AINodeValidatorAIOutsideFOV::Evaluate( uint32 dwFilteredStatusFlags, const LTVector& vAIPos, const LTVector& vNodePos, const LTVector& vNodeForward, bool bIgnoreDir ) const
{
	if( dwFilteredStatusFlags & kNodeStatus_AIOutsideFOV )
	{
		if( !bIgnoreDir )
		{
			LTVector vAIDir = vAIPos - vNodePos;
			vAIDir.y = 0.f;
			vAIDir.Normalize();

			if ( vAIDir.Dot(vNodeForward) <= m_fFovDp )
			{
				return false;
			}
		}
	}

	return true;
}