//-----------------------------------------------------------------------------
//  ApplyExplosionPart
//-----------------------------------------------------------------------------
void    CPhysicObj::ApplyExplosionPart (int nPartIdx, float fForce, const NxVec3& vPos)
{
    assert( m_bActivated && (nPartIdx < GetNumParts()) );

	// Solo podemos aplicar fuerzas a objetos físicos dinámicos
	if (!IsDynamic())	return;

    NxActor*    pActor = GetActor( nPartIdx );

    // Aplicamos una fuerza en cada shape, proporcional a su volumen.
    // NOTA: Para que fuese mas realista realmente habria que modular la 
    //       fuerza en funcion de la superficie de proyeccion de cada shape
    //       hacia el punto de origen de la explosion, para aproximar lo que
    //       seria la superficie de impacto.
    uint    nNumShapes = pActor->getNbShapes();
    assert( nNumShapes > 0 );

    NxShape* const* pShapes = pActor->getShapes(); 
    for (uint i = 0; i < nNumShapes; i++)
    {
        NxShape*    pShape = pShapes[i];
        // - Calcular BBox de la shape
        NxBox       shapeBox = PhysicUtils::CalcOBBox( *pShape );
        // - Calcular punto de impacto de la explosion
        NxVec3      vImpactPoint = PhysicUtils::CalcExplosionImpact( shapeBox, vPos );
        //NxVec3      vImpactPoint = shapeBox.GetCenter();
        // - Modular la fuerza de la explosion por el area expuesta de la shape
        float       fVolume     = (shapeBox.extents * 2.f).magnitudeSquared();            
        float       fForceMod   = fForce * fVolume;
        // - Modular a su vez en funcion de la distancia al centro de la explosion
        //   usando una funcion exponencial de atenuacion
        NxVec3      vImpactDir  = vImpactPoint - vPos;
        float       fDist       = vImpactDir.normalize();
        // NOTA: vamos a marcar una zona de radio minimo donde se aplique la fuerza maxima
        //static float s_fMinDist = 0.1f;
        //fDist += s_fMinDist;
        static float s_fAttenuationFactor = 0.05f;
        fForceMod *= exp( -s_fAttenuationFactor * fDist );
        // - Aplicar la fuerza en el punto de impacto
        pActor->addForceAtPos( vImpactDir * fForceMod, vImpactPoint, NX_IMPULSE );
    }
}