static void Event_BulletImpact ( void )
{
    if ( m_pBulletImpactHandler )
    {
        CPed * pInitiator = m_pools->GetPed ( (DWORD *)pBulletImpactInitiator );
        if ( pInitiator )
        {
            CEntity* pVictim = m_pools->GetEntity ( (DWORD *)pBulletImpactVictim );

            if ( IsLocalPlayer ( pInitiator ) )
            {
                // Correct weapon range if local player
                float fRange = pInitiator->GetCurrentWeaponRange ();
                CVector vecDir = *pBulletImpactEndPosition - *pBulletImpactStartPosition;
                float fLength = vecDir.Length ();
                if ( fRange < fLength )
                {
                    vecDir.Normalize ();
                    *pBulletImpactEndPosition = *pBulletImpactStartPosition + vecDir * fRange;
                }
                // These two will be the same when shooting without aiming, so correct them
                if ( vecLastLocalPlayerBulletStart == vecLastLocalPlayerBulletEnd )
                {
                    vecLastLocalPlayerBulletStart = *pBulletImpactStartPosition;
                    vecLastLocalPlayerBulletEnd = *pBulletImpactEndPosition;
                }
                m_pBulletImpactHandler ( pInitiator, pVictim, &vecLastLocalPlayerBulletStart, &vecLastLocalPlayerBulletEnd );
            }
            else
            {
                // Correct start postion if remote player
                CRemoteDataStorageSA * data = CRemoteDataSA::GetRemoteDataStorage ( pBulletImpactInitiator );
                if ( data )
                {
                    if ( data->ProcessPlayerWeapon () )
                    {
                        if ( data->m_shotSyncData.m_bRemoteBulletSyncVectorsValid )
                        {
                            *pBulletImpactStartPosition = data->m_shotSyncData.m_vecRemoteBulletSyncStart;
                            data->m_shotSyncData.m_bRemoteBulletSyncVectorsValid = false;

                            // Ensure weapon fire event gets the correct vectors
                            data->m_shotSyncData.m_vecShotOrigin = data->m_shotSyncData.m_vecRemoteBulletSyncStart;
                            data->m_shotSyncData.m_vecShotTarget = data->m_shotSyncData.m_vecRemoteBulletSyncEnd;
                        }
                        else
                            *pBulletImpactStartPosition = data->m_shotSyncData.m_vecShotOrigin;
                    }
                }
                m_pBulletImpactHandler ( pInitiator, pVictim, pBulletImpactStartPosition, pBulletImpactEndPosition );
            }
        }
        vecSavedBulletImpactEndPosition = *pBulletImpactEndPosition;    // Saved for vehicle damage event parameters
    }
}