void CAutoDefenseClass::Update (CInstalledDevice *pDevice, 
								CSpaceObject *pSource, 
								int iTick,
								bool *retbSourceDestroyed,
								bool *retbConsumedItems)

//	Update
//
//	Update device

	{
	if (pDevice->IsReady() && pDevice->IsEnabled())
		{
		int i;

		//	Look for a target

		CSpaceObject *pBestTarget = NULL;
		Metric rBestDist2 = MAX_INTERCEPT_DISTANCE * MAX_INTERCEPT_DISTANCE;

		for (i = 0; i < pSource->GetSystem()->GetObjectCount(); i++)
			{
			CSpaceObject *pObj = pSource->GetSystem()->GetObject(i);

			if (pObj
					&& pObj->GetCategory() == CSpaceObject::catMissile
					&& pObj->GetSource() != pSource
					&& (pObj->GetSource() == NULL || pSource->IsEnemy(pObj->GetSource())))
				{
				CVector vRange = pObj->GetPos() - pSource->GetPos();
				Metric rDistance2 = vRange.Dot(vRange);

				if (rDistance2 < rBestDist2)
					{
					pBestTarget = pObj;
					rBestDist2 = rDistance2;
					}
				}
			}

		//	If we found a target, try to shoot at it

		if (pBestTarget)
			{
			CDeviceClass *pWeapon = GetWeapon();

			if (pWeapon)
				{
				int iFireAngle;
				if (pWeapon->IsWeaponAligned(pSource, pDevice, pBestTarget, &iFireAngle))
					{
					pDevice->SetFireAngle(iFireAngle);
					pWeapon->Activate(pDevice, pSource, pBestTarget, iFireAngle, retbSourceDestroyed, retbConsumedItems);
					pDevice->SetActivationDelay(m_iRechargeTicks);
					}
				}
			}
		}
	}