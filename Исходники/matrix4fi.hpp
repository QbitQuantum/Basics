	/**
	 * Constructs a look-at matrix
	 *
	 */
	void lookAt ( const Vector3f &eye,
				  const Vector3f &up,
				  const Vector3f &at )
	{
		Vector3f zaxis = (at - eye).normalize( );
		Vector3f xaxis = up.cross( zaxis ).normalize( );
		Vector3f yaxis = zaxis.cross( xaxis );

		// X, Y, X will now be used as a orthonormal basis
		m_matrix[0][0] = FLT2FIX( xaxis.m_x );
		m_matrix[0][1] = FLT2FIX( xaxis.m_y );
		m_matrix[0][2] = FLT2FIX( xaxis.m_z );
		m_matrix[0][3] = FLT2FIX( -xaxis.dot( eye.m_x )  );

		m_matrix[1][0] = FLT2FIX( yaxis.m_x );
		m_matrix[1][1] = FLT2FIX( yaxis.m_y );
		m_matrix[1][2] = FLT2FIX( yaxis.m_z );
		m_matrix[1][3] = FLT2FIX( -yaxis.dot( eye.m_y ) );

		m_matrix[2][0] = FLT2FIX( zaxis.m_x );
		m_matrix[2][1] = FLT2FIX( zaxis.m_y );
		m_matrix[2][2] = FLT2FIX( zaxis.m_z );
		m_matrix[2][3] = FLT2FIX( -zaxis.dot( eye.m_z )  );

		m_matrix[3][0] = 0;
		m_matrix[3][1] = 0;
		m_matrix[3][2] = 0;
		m_matrix[3][3] = FIX_ONE;
	}