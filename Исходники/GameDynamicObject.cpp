void GameDynamicObject::update( float dt )
{
	GameObject::update( dt );

	if ( m_spinSpeed > 0.f )
		setRotation( rotation() * Matrix3x3( m_spinAxis, m_spinSpeed * dt) );

	if ( m_worldAnim )
	{
		m_worldAnimTime += dt;

		//Animatable* anims[] = {m_worldAnim};
		//float weight = 1.f;
		//m_geometry->blendState( anims, &m_worldAnimTime, &weight, 1 );
		m_geometry->setTransform( m_worldAnim->transform() );

		Matrix4x4 tm = m_geometry->worldTransform();
		moveWithoutColliding( tm.translation() - position() );
		setRotation( tm.rotation() );
	}

	m_geometry->setTransform( transform() );
}