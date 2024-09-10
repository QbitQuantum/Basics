void CNametags::DrawFromAim()
{
    unsigned long ulCurrentTime = CClientTime::GetTime();

    // Got any players that are not local?
    if (m_pPlayerManager->Count() > 1)
    {
        // Grab the local player
        CClientPlayer* pLocalPlayer = m_pPlayerManager->GetLocalPlayer();
        if (pLocalPlayer)
        {
            // Grab the current time and the camera
            unsigned long ulCurrentTime = CClientTime::GetTime();
            CCamera*      pCamera = g_pGame->GetCamera();

            // Grab our controller state
            CControllerState State;
            g_pGame->GetPad()->GetCurrentControllerState(&State);

            // Grab our current weapon slot. Use screen center if melee or none
            CVector     vecStart;
            CVector     vecTarget;
            eWeaponSlot eSlot = pLocalPlayer->GetCurrentWeaponSlot();
            if (eSlot == WEAPONSLOT_TYPE_UNARMED || eSlot == WEAPONSLOT_TYPE_MELEE || eSlot == WEAPONSLOT_TYPE_RIFLE || eSlot == WEAPONSLOT_TYPE_THROWN ||
                eSlot == WEAPONSLOT_TYPE_SPECIAL || eSlot == WEAPONSLOT_TYPE_GIFT || eSlot == WEAPONSLOT_TYPE_PARACHUTE || eSlot == WEAPONSLOT_TYPE_DETONATOR)
            {
                // Grab the active cam
                CCamera* pCamera = g_pGame->GetCamera();
                CCam*    pActive = pCamera->GetCam(pCamera->GetActiveCam());

                // Grab the camera matrix
                CMatrix matCamera;
                pCamera->GetMatrix(&matCamera);
                vecStart = matCamera.vPos;

                // Range
                float        fRange;
                eWeaponType  eWeapon = pLocalPlayer->GetCurrentWeaponType();
                float        fSkill = pLocalPlayer->GetStat(g_pGame->GetStats()->GetSkillStatIndex(eWeapon));
                CWeaponStat* pWeaponStat = g_pGame->GetWeaponStatManager()->GetWeaponStatsFromSkillLevel(eWeapon, fSkill);
                if (pWeaponStat)
                {
                    fRange = pWeaponStat->GetTargetRange();
                }
                else
                {
                    fRange = MELEE_VISIBLE_RANGE;
                }

                // Find the target position
                CVector vecFront = *pActive->GetFront();
                vecFront.Normalize();
                vecTarget = *pActive->GetSource() + vecFront * fRange;
            }
            else
            {
                // Grab the weapon and keysync state. If it exists and he holds Target down
                CWeapon* pPlayerWeapon = pLocalPlayer->GetWeapon();
                if (pPlayerWeapon && State.RightShoulder1)
                {
                    // Grab the gun muzzle position
                    eWeaponType  eWeapon = pLocalPlayer->GetCurrentWeaponType();
                    float        fSkill = pLocalPlayer->GetStat(g_pGame->GetStats()->GetSkillStatIndex(eWeapon));
                    CWeaponStat* pWeaponStat = g_pGame->GetWeaponStatManager()->GetWeaponStatsFromSkillLevel(eWeapon, fSkill);

                    CVector vecGunMuzzle = *pWeaponStat->GetFireOffset();
                    pLocalPlayer->GetTransformedBonePosition(BONE_RIGHTWRIST, vecGunMuzzle);

                    // Grab the target point
                    pCamera->Find3rdPersonCamTargetVector(AIM_VISIBLE_RANGE, &vecGunMuzzle, &vecStart, &vecTarget);
                }
                else
                {
                    // Grab the active cam
                    CCam* pActive = pCamera->GetCam(pCamera->GetActiveCam());

                    // Grab the camera matrix
                    CMatrix matCamera;
                    pCamera->GetMatrix(&matCamera);
                    vecStart = matCamera.vPos;

                    // Find the target position
                    CVector vecFront = *pActive->GetFront();
                    vecFront.Normalize();
                    vecTarget = *pActive->GetSource() + vecFront * MELEE_VISIBLE_RANGE;
                }
            }

            // Ignore the local player for this
            pLocalPlayer->WorldIgnore(true);

            // Do the raycast
            CColPoint*        pColPoint = NULL;
            CEntity*          pEntity = NULL;
            SLineOfSightFlags flags;
            flags.bCheckBuildings = true;
            flags.bCheckVehicles = true;
            flags.bCheckPeds = true;
            flags.bCheckObjects = true;
            flags.bCheckDummies = true;
            flags.bSeeThroughStuff = true;
            flags.bIgnoreSomeObjectsForCamera = false;
            flags.bShootThroughStuff = true;
            g_pGame->GetWorld()->ProcessLineOfSight(&vecStart, &vecTarget, &pColPoint, &pEntity, flags);
            if (pColPoint)
                pColPoint->Destroy();

            // Un-ignore the local player
            pLocalPlayer->WorldIgnore(false);

            // Did we find an entity?
            if (pEntity)
            {
                // Grab the CClientEntity belonging to this game_sa entity
                CClientEntity* pClientEntity = reinterpret_cast<CClientEntity*>(pEntity->GetStoredPointer());
                if (pClientEntity)
                {
                    // Is it a vehicle? Is it a ped?
                    eClientEntityType EntityType = pClientEntity->GetType();
                    if (EntityType == CCLIENTVEHICLE)
                    {
                        CClientVehicle* pClientVehicle = static_cast<CClientVehicle*>(pClientEntity);

                        // Set the current time as the last draw time for all players inside
                        CClientPed* pPed;
                        int         i;
                        for (i = 0; i < 8; i++)
                        {
                            // Grab this seat's occupant and set its last nametag show time to now
                            pPed = pClientVehicle->GetOccupant(i);
                            if (pPed && pPed->GetType() == CCLIENTPLAYER)
                            {
                                static_cast<CClientPlayer*>(pPed)->SetLastNametagShow(ulCurrentTime);
                            }
                        }
                    }
                    else if (EntityType == CCLIENTPLAYER)
                    {
                        // Grab the player this entity is
                        CClientPlayer* pClientPlayer = static_cast<CClientPlayer*>(pClientEntity);
                        if (pClientPlayer)
                        {
                            // Set now as the last time we had the cursor above him
                            pClientPlayer->SetLastNametagShow(ulCurrentTime);
                        }
                    }
                }
            }

            // Grab the local player vehicle
            CClientVehicle* pLocalVehicle = pLocalPlayer->GetOccupiedVehicle();

            // Draw the nametags we need to
            CClientPlayer*                              pPlayer;
            CClientStreamElement*                       pElement;
            list<CClientStreamElement*>::const_iterator iter = m_pPlayerStreamer->ActiveElementsBegin();
            for (; iter != m_pPlayerStreamer->ActiveElementsEnd(); ++iter)
            {
                pElement = *iter;
                if (!pElement->IsStreamedIn())
                    continue;
                if (pElement->GetType() != CCLIENTPLAYER)
                    continue;
                pPlayer = static_cast<CClientPlayer*>(pElement);
                if (pPlayer->IsLocalPlayer())
                    continue;

                // Is he in the same vehicle as the local player?
                if (pLocalVehicle && pPlayer->GetOccupiedVehicle() == pLocalVehicle)
                {
                    pPlayer->SetLastNametagShow(ulCurrentTime);
                }

                // Can we show this player's nametag
                unsigned long ulLastNametagShow = pPlayer->GetLastNametagShow();
                if (ulLastNametagShow != 0 && ulCurrentTime <= ulLastNametagShow + NAMETAG_END_FADE_TIME)
                {
                    unsigned long ulLastNametagShow = pPlayer->GetLastNametagShow();
                    // Calculate the alpha modifier
                    float fAlphaTimeModifier;
                    if (ulCurrentTime < ulLastNametagShow + NAMETAG_BEGIN_FADE_TIME)
                    {
                        fAlphaTimeModifier = 1.0f;
                    }
                    else
                    {
                        fAlphaTimeModifier = 1.0f - (ulCurrentTime - ulLastNametagShow - NAMETAG_BEGIN_FADE_TIME) / 1000.0f;
                    }

                    // Calculate the alpha for the nametag
                    unsigned char ucAlpha = static_cast<unsigned char>(180.0f * fAlphaTimeModifier);

                    // Draw it
                    DrawTagForPlayer(pPlayer, ucAlpha);
                }
            }
        }
    }
}