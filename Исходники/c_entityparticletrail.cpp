//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void C_EntityParticleTrail::AddParticle( float flInitialDeltaTime, const Vector &vecMins, const Vector &vecMaxs, const matrix3x4_t &boxToWorld )
{
    // Select a random point somewhere in the hitboxes of the entity.
    Vector vecLocalPosition, vecWorldPosition;
    vecLocalPosition.x			= Lerp( random->RandomFloat( 0.0f, 1.0f ), vecMins.x, vecMaxs.x );
    vecLocalPosition.y			= Lerp( random->RandomFloat( 0.0f, 1.0f ), vecMins.y, vecMaxs.y );
    vecLocalPosition.z			= Lerp( random->RandomFloat( 0.0f, 1.0f ), vecMins.z, vecMaxs.z );
    VectorTransform( vecLocalPosition, boxToWorld, vecWorldPosition );

    // Don't emit the particle unless it's inside the model
    if ( m_hConstraintEntity.Get() )
    {
        Ray_t ray;
        trace_t tr;
        ray.Init( vecWorldPosition, vecWorldPosition );
        enginetrace->ClipRayToEntity( ray, MASK_ALL, m_hConstraintEntity, &tr );

        if ( !tr.startsolid )
            return;
    }

    // Make a new particle
    SimpleParticle *pParticle = (SimpleParticle *)m_ParticleEffect.AddParticle( sizeof(SimpleParticle), m_hMaterial );
    if ( pParticle == NULL )
        return;

    pParticle->m_Pos			= vecWorldPosition;
    pParticle->m_flRoll			= Helper_RandomInt( 0, 360 );
    pParticle->m_flRollDelta	= Helper_RandomFloat( -2.0f, 2.0f );

    pParticle->m_flLifetime		= flInitialDeltaTime;
    pParticle->m_flDieTime		= m_Info.m_flLifetime;

    pParticle->m_uchColor[0]	= 64;
    pParticle->m_uchColor[1]	= 140;
    pParticle->m_uchColor[2]	= 225;
    pParticle->m_uchStartAlpha	= Helper_RandomInt( 64, 64 );
    pParticle->m_uchEndAlpha	= 0;

    pParticle->m_uchStartSize	= m_Info.m_flStartSize;
    pParticle->m_uchEndSize		= m_Info.m_flEndSize;

    pParticle->m_vecVelocity	= vec3_origin;
    VectorMA( pParticle->m_Pos, flInitialDeltaTime, pParticle->m_vecVelocity, pParticle->m_Pos );
}