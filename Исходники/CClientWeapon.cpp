void CClientWeapon::FireInstantHit ( CVector vecOrigin, CVector vecTarget, bool bServerFire, bool bRemote )
#endif
{
    CVector vecDirection = vecTarget - vecOrigin;
    vecDirection.Normalize ();
    CClientEntity * pAttachedTo = GetAttachedTo ();    
    CVector vecOriginalTarget = vecTarget;
    CEntity * pColEntity = NULL;
    CColPoint * pColPoint = NULL;
    SLineOfSightBuildingResult pBuildingResult;
    CEntitySAInterface * pEntity = NULL;

    if ( m_Type != WEAPONTYPE_SHOTGUN )
    {
        CVector vecWeaponFirePosition;
        if ( !IsLocalEntity ( ) && m_pOwner )
        {
            CClientPlayer * pPlayer = m_pOwner;
            CClientPed * pLocalPlayer = g_pClientGame->GetLocalPlayer();
            if ( pLocalPlayer && pPlayer )
            {
                CClientVehicle* pVehicle = pLocalPlayer->GetRealOccupiedVehicle ();

                // Move both players to where they should be for shot compensation
                if ( pPlayer && !pPlayer->IsLocalPlayer () )
                {
                    if ( !pVehicle || pLocalPlayer->GetOccupiedVehicleSeat() == 0 )
                    {
                        // Warp back in time to where we were when this player shot (their latency)

                        // We don't account for interpolation here, +250ms seems to work better
                        // ** Changed ajustment to +125ms as the position of this clients player on the firers screen
                        // has been changed. See CClientPed::UpdateTargetPosition() **
                        CVector vecPosition;
                        unsigned short usLatency = ( pPlayer->GetLatency () + 125 );
                        g_pClientGame->GetNetAPI()->GetInterpolation ( vecPosition, usLatency );

                        // Move the entity back
                        if ( pVehicle )
                        {
                            pVehicle->GetPosition ( vecWeaponFirePosition );
                            pVehicle->SetPosition ( vecPosition, false, false );
                        }
                        else
                        {
                            pLocalPlayer->GetPosition ( vecWeaponFirePosition );
                            pLocalPlayer->SetPosition ( vecPosition, false, false );
                        }
                    }
                }
            }
        }
        //if ( pAttachedTo ) pAttachedTo->WorldIgnore ( true );
        if ( m_pWeapon->ProcessLineOfSight ( &vecOrigin, &vecTarget, &pColPoint, &pColEntity, m_weaponConfig.flags, &pBuildingResult, m_Type, &pEntity ) )
        {
            vecTarget = pColPoint->GetPosition ();
        }

        // Don't continue without a valid colpoint
        if ( !pColPoint )
            return;
        //if ( pAttachedTo ) pAttachedTo->WorldIgnore ( false );

        // return if shoot if target is blocked is false and we aren't pointing at our target
        if ( ( m_pTarget != NULL && m_pTarget->GetGameEntity ( ) != NULL && m_pTarget->GetGameEntity()->GetInterface ( ) != pEntity ) && m_weaponConfig.bShootIfTargetBlocked == false && bRemote == false )
        {
            if ( pColPoint )
                pColPoint->Destroy ();

            return;
        }
        // Execute our weapon fire event
        CClientEntity * pClientEntity = m_pManager->FindEntitySafe ( pColEntity );
        CLuaArguments Arguments;
        if ( pClientEntity )
            Arguments.PushElement ( pClientEntity );            // entity that got hit
        else
            Arguments.PushNil ( ); // Probably a building.
        Arguments.PushNumber ( pColPoint->GetPosition ( ).fX ); // pos x
        Arguments.PushNumber ( pColPoint->GetPosition ( ).fY ); // pos y
        Arguments.PushNumber ( pColPoint->GetPosition ( ).fZ ); // pos z
        Arguments.PushNumber ( pColPoint->GetNormal ( ).fX ); // Normal x
        Arguments.PushNumber ( pColPoint->GetNormal ( ).fY ); // Normal y
        Arguments.PushNumber ( pColPoint->GetNormal ( ).fZ ); // Normal z
        Arguments.PushNumber ( pColPoint->GetSurfaceTypeB ( ) ); // Surface type "B"
        Arguments.PushNumber ( pColPoint->GetLightingForTimeOfDay ( ) ); // Lighting
        Arguments.PushNumber ( pColPoint->GetPieceTypeB ( ) ); // Piece
        if ( !CallEvent ( "onClientWeaponFire", Arguments, true ) )
        {
            if ( pColPoint )
                pColPoint->Destroy ();
            return;
        }

        DoGunShells ( vecOrigin, vecDirection );

        CVector vecCollision;
        if ( g_pGame->GetWaterManager ()->TestLineAgainstWater ( vecOrigin, vecTarget, &vecCollision ) )
        {
            g_pGame->GetFx ()->TriggerBulletSplash ( vecCollision );
            g_pGame->GetAudioEngine ()->ReportBulletHit ( NULL, SURFACE_TYPE_WATER_SHALLOW, &vecCollision, 0.0f );
        }    
#ifdef MARKER_DEBUG
        m_pMarker2->SetPosition ( vecTarget );
#endif
        m_pWeapon->DoBulletImpact ( m_pObject, pEntity, &vecOrigin, &vecTarget, pColPoint, 0 );

        if ( !IsLocalEntity ( ) && m_pOwner )
        {
            CClientPed * pPed = m_pOwner;
            CClientPed * pLocalPlayer = g_pClientGame->GetLocalPlayer();
            if ( pPed->GetType () == CCLIENTPLAYER )
            {
                // Restore compensated positions            
                if ( !pPed->IsLocalPlayer () )
                {
                    CClientVehicle* pVehicle = pLocalPlayer->GetRealOccupiedVehicle ();
                    if ( !pVehicle )
                    {
                        pLocalPlayer->SetPosition ( vecWeaponFirePosition, false, false );
                    }
                    else if ( pLocalPlayer->GetOccupiedVehicleSeat() == 0 )
                    {
                        pVehicle->SetPosition ( vecWeaponFirePosition, false, false );
                    }
                }
            }
        }
        if ( !IsLocalEntity ( ) && GetOwner ( ) == g_pClientGame->GetLocalPlayer ( ) && bServerFire == false )
        {
            g_pClientGame->GetNetAPI ( )->SendBulletSyncCustomWeaponFire ( this, vecOrigin, vecOriginalTarget );
        }
    }
#ifdef SHOTGUN_TEST
    else
    {
        //if ( pAttachedTo ) pAttachedTo->WorldIgnore ( true );
        //if ( pAttachedTo ) pAttachedTo->WorldIgnore ( false );
        // Fire instant hit is off by a few degrees
        FireShotgun ( m_pObject, vecOrigin, vecTarget, vecRotation );
    }
#endif
    if ( pColPoint )
        pColPoint->Destroy ();
}