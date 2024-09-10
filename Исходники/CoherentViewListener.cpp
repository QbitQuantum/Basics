    bool CCoherentViewListener::RaycastGeometry( const Vec3& origin, const Vec3& dir, float& outDist, int& outViewX, int& outViewY )
    {
        if ( !m_pView || !m_Geometry )
        {
            return false;
        }

        IEntity* pEntity = gEnv->pEntitySystem->FindEntityByName( m_EngineObjectName.c_str() );

        if ( pEntity )
        {
            const Matrix34& invWorldMatrix = pEntity->GetWorldTM().GetInverted();
            Vec3 originModelSpace = invWorldMatrix.TransformPoint( origin );
            Vec3 dirModelSpace = invWorldMatrix.TransformVector( dir );
            dirModelSpace.Normalize();

            float t, u, v;

            if ( m_Geometry->IntersectWithRay( originModelSpace, dirModelSpace, t, u, v ) )
            {
                outDist = t;
                outViewX = ( int )( m_pView->GetWidth() * u );
                outViewY = ( int )( m_pView->GetHeight() * v );
                return true;
            }
        }

        return false;
    }