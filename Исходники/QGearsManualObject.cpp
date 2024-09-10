    //-------------------------------------------------------------------------
    void
    ManualObject::position( const Ogre::Vector3 &position )
    {
        if( m_position == nullptr )
        {
            createPositionBuffer();
        }
        *(m_position++) = position;

		m_bbox.merge( position );
		m_radius = std::max( m_radius, position.length() );
    }