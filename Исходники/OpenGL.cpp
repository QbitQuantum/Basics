	void GL::orthoTranslation( Matrix4f& mat, float left, float right, float top, float bottom, float transx, float transy, float near, float far, bool fliph )
	{
		if( fliph ) {
			float tmp = top;
			top = bottom;
			bottom = tmp;
		}
		mat.setZero();
		mat[ 0 ][ 0 ]  = 2.0f / ( right - left );
		mat[ 0 ][ 3 ]  = - ( right + left ) / ( right - left );
		mat[ 0 ][ 3 ] += transx * mat[ 0 ][ 0 ];

		mat[ 1 ][ 1 ]  = 2.0f / ( top - bottom );
		mat[ 1 ][ 3 ]  = - ( top + bottom ) / ( top - bottom );
		mat[ 1 ][ 3 ] += transy * mat[ 1 ][ 1 ];

		mat[ 2 ][ 2 ]  = -2.0f / ( far - near );
		mat[ 2 ][ 3 ]  = - ( far + near ) / ( far - near );

		mat[ 3 ][ 3 ]  = 1.0f;
	}