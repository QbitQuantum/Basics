	//--------------------------------------------------------------------------------
	bool CJob::SetUILimitExitWindows( bool bLimit )
	{
		_WINQ_FCONTEXT( "CJob::SetUILimitExitWindows" );
		bool bResult = false;
		__QOR_PROTECT
		{
			sJobObjectBasicUIRestrictions UILimits = GetUILimits();
			if( bLimit )
			{
				UILimits.UIRestrictionsClass |= eJobObjectUILimit_ExitWindows;
			}
			else
			{
				UILimits.UIRestrictionsClass &= (~eJobObjectUILimit_ExitWindows);
			}
			bResult = SetInformationJobObject( JobObjectBasicUIRestrictions, &UILimits, sizeof( sJobObjectBasicUIRestrictions ) ) ? true : false;
		}__QOR_ENDPROTECT
		return bResult;
	}