    //-----------------------------------------------------------------------------
    //  Update
    //  Updates the object
    //  TODO: Pre- and Post- updates?
    //-----------------------------------------------------------------------------
    void CView::Update( void )
    {
        RVector4 x, y, z;

        z = m_vLook = Normalize( m_vLook );
        x = m_vRight = Normalize( CrossProduct( m_vUp, z ) );
        y = CrossProduct( z, x );
        
        m_mView.r0 = x;
        m_mView.r1 = y;
        m_mView.r2 = z;
        m_mView.r3 = RVector4Zero();
        m_mView = Transpose( m_mView );
        
        m_mView.r3 = RVector4( -DotProduct( x, m_vPosition), -DotProduct( y, m_vPosition), -DotProduct( z, m_vPosition), 1.0f );

        
        //z = Normalize( RQuatGetZAxis(m_Transform.orientation) );
        //x = Normalize( CrossProduct( RVector3(0.0f,1.0f,0.0f), z ) );
        //y = CrossProduct( z, x );
        //
        //m_mView.r0 = Homogonize( x );
        //m_mView.r1 = Homogonize( y );
        //m_mView.r2 = Homogonize( z );
        //m_mView.r3 = RVector4Zero();
        //m_mView = Transpose( m_mView );
        //
        //m_mView.r3 = RVector4( -DotProduct( x, m_Transform.position), -DotProduct( y, m_Transform.position), -DotProduct( z, m_Transform.position), 1.0f );
    
        char szCameraData[256] = { 0 };

        sprintf( szCameraData, "Pos:  %f, %f, %f", m_vPosition.x, m_vPosition.y, m_vPosition.z );
        Engine::GetRenderer()->DrawString( 200, 16, szCameraData );
        sprintf( szCameraData, "Look: %f, %f, %f", m_vLook.x, m_vLook.y, m_vLook.z );
        Engine::GetRenderer()->DrawString( 200, 32, szCameraData );
    }