	void ProcessEvent( EFlowEvent event, SActivationInfo *pActInfo )
	{
		if(eFE_Activate == event && IsPortActive(pActInfo,0))
		{
			IActor* pActor = GetActor(pActInfo);
			if (pActor == 0)
				return;

			CWeapon* pWeapon = static_cast<CWeapon*> (GetWeapon(pActor));
			bool bZoomed = false;
			if (pWeapon != 0)
			{
				const string& weaponClass = GetPortString(pActInfo, 1);
				if (weaponClass.empty() == true || weaponClass == pWeapon->GetEntity()->GetClass()->GetName())
				{
					bZoomed = pWeapon->IsZoomed();
				}
			}
			ActivateOutput(pActInfo, bZoomed ? 1 : 0, true);			
		}
	}