door::door						( CPhysicObject* object ) :
	m_object					( *object ),
	m_state						( door_state_open ),
	m_previous_state			( door_state_open ),
	m_target_state				( door_state_open ),
	m_registered_position		( object->Position() ),
	m_locked					( false )
{
	VERIFY						( valid(m_state) );
	VERIFY						( valid(m_target_state) );
	VERIFY						( valid(m_previous_state) );

	R_ASSERT					( m_object.get_door_vectors( m_closed_vector, m_open_vector ) );

	Fmatrix invert;
	invert.invert				( m_object.XFORM() );
	invert.transform_dir		( m_open_vector );
	invert.transform_dir		( m_closed_vector );

	float const length			= 1.1f;
	m_open_vector.mul			( length );
	m_closed_vector.mul			( length );

	m_object.spatial.type		|=	STYPE_VISIBLEFORAI;
}