void CObject::ObjectDamage(float damage, CVector* vec1, CVector* vec2, CEntity* damager, eWeaponType weapon_type)
{
    if(m_bUsesCollision)
    {
        return;
    }
    if(weapon_type == 55 && damager && damager->entityType == ENTITY_TYPE_VEHICLE)
    {
        weapon_type == 50;
    }
    if(!CanPhysicalBeDamaged(weapon_type, NULL))
    {
        return;
    }
    m_fHealth = Max(m_fHealth - damage * m_pObjectInfo->fColDamageMultiplier, 0.0);
    if(m_colDamageEffect == 0 || (m_bInvulnerable && damager != getPlayerPed(-1) && damager != getPlayerVehicle(-1, 0)))
    {
        return;
    }
    if(m_nModelIndex == MODEL_INDEX_IMY_SMASH_WALL)
    {
        // vehicle must be SWAT Water Cannon Vehicle
        CVehicle *veh = damager;
        if(!veh)
        {
            return;
        }
        switch(damager->entityType)
        {
            case ENTITY_TYPE_PED:
                if(!damager->pedFlags.bInVehicle || !damager->pCurrentObjective)
                {
                    return;
                }
                veh = damager->pCurrentObjective;
            break;
            case ENTITY_TYPE_VEHICLE:
            break;
            default:
                return;
        }
        if(veh->m_nModelIndex != 601)
        {
            return;
        }
    }
    // must not be a Forklift
    if(damager && damager->m_nModelIndex == MODEL_INDEX_FORKLIFT)
    {
        return;
    }
    m_breakWeaponType = weapon_type;
    if(damage * m_pObject->fColDamageMultiplier > 150.0)
    {
        switch(m_colDamageEffect)
        {
            case 200:
            case 202:
            {
                bool smashed = false;
                if(m_pObjectInfo->fSmashMultiplier * 150.0 < damage * m_pObjectInfo->fColDamageMultiplier)
                {
                    smashed = true;
                }
                BreakableInfoPool.Add(this, m_pObjectInfo->breakVelocity, m_pObjectInfo->fBreakVelocityRand, smashed);
                m_bUsesCollision = false;
                m_bIsVisible = false;
                if(!IsStatic())
                {
                    RemoveFromMovingList();
                }
                m_bExplosionProof = true;
                m_bIsStatic = true;
                m_vecLinearVelocity = 0;
                m_vecAngularVelocity = 0;
                m_bBroken = true;
                DeleteRwObject();
                v14 = 1; // v14: advancedDamage ( needs audio + explosion) # basic is only fx
            }
            break;
            case 1:
                if(!bRenderDamaged)
                {
                    DeleteRwObject();
                    v14 = 1;
                }
            break;
            case 20:
                m_bUsesCollision = false;
                m_bIsVisible = false;
                if(!IsStatic())
                {
                    RemoveFromMovingList();
                }
                m_bIsStatic = true;
                m_bExplosionProof = true;
                m_vecLinearVelocity = 0;
                m_vecAngularVelocity = 0;
                DeleteRwObject();
                v14 = 1;
            break;
            case 21:
                if(m_bRenderDamaged)
                {
                    m_bUsesCollision = false;
                    m_bIsVisible = false;
                    if(!IsStatic())
                    {
                        RemoveFromMovingList();
                    }
                    m_bIsStatic = true;
                    m_bExplosionProof = true;
                    m_vecLinearVelocity = 0;
                    m_vecAngularVelocity = 0;
                    DeleteRwObject();
                    v14 = 1;
                }
                else
                {
                    DeleteRwObject();
                    m_bRenderDamaged = true;
                }
            break;
        }
        if(m_bUsesCollision && m_bIsVisible)
        {
            m_fHealth = 0.0;
        }
    }
    bool exploded = false;
    if(v14 == 1)
    {
        if(TryToExplode())
        {
            exploded = true;
        }
        CAudio::ProcessBrokenObject(this);
    }
    if(!exploded || !v14)
    {
        v27 = m_pObjectInfo->fxType == 3;
        if(v14 == 0)
        {
            if(m_pObjectInfo->fxType != 1)
            {
                return;
            }
            v27 = damage > 30.0;
        }
        else
        {
            v27 = m_pObjectInfo->fxType == 2;
        }
        if(v27)
        {
            if(m_pObjectInfo->fxOffset.x >= -500.0)
            {
                CMatrix pos = CMatrix::FromXYZ(m_xyz);
                // to object space
                CVector fx_obj_pos = pos * m_pObjectInfo->fxOffset;
                fx_obj_pos += GetPos(); // to world space
                FxSystem_c *sys = FxManager.InitialiseFxSystem(m_pObjectInfo->pFxSystemBP, fx_obj_pos, 0, 0);
                if(sys)
                {
                    sys->Start();
                }    
            }
            else
            {
                if(!offset)
                {
                    return;
                }
                RwMatrix matrix;
                Fx_c::CreateMatFromVec(matrix, offset, rotation);
                FxSystem_c *sys = FxManager.InitialiseFxSystem(m_pObjectInfo->pFxSystemBP, matrix, 0, 0);
                if(sys)
                {
                    sys->Start();
                }
            }
        }
    }
}