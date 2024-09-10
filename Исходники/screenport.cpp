bool Screenport::ViewToWorld( const grinliz::Vector2F& v, const grinliz::Matrix4* _mvpi, grinliz::Ray* ray ) const
{
	Matrix4 mvpi;
	if ( _mvpi ) {
		mvpi = *_mvpi;
	}
	else {
		Matrix4 mvp;
		ViewProjection3D( &mvp );
		mvp.Invert( &mvpi );
	}

	// View normalized:
	Vector4F in = { 2.0f * v.x / screenWidth - 1.0f,
					2.0f * v.y / screenHeight - 1.0f,
					0.f, //v.z*2.0f-1.f,
					1.0f };

	Vector4F out0, out1;
	MultMatrix4( mvpi, in, &out0 );
	in.z = 1.0f;
	MultMatrix4( mvpi, in, &out1 );

	if ( out0.w == 0.0f ) {
		return false;
	}
	ray->origin.x = out0.x / out0.w;
	ray->origin.y = out0.y / out0.w;
	ray->origin.z = out0.z / out0.w;

	ray->direction.x = out1.x / out1.w - ray->origin.x;
	ray->direction.y = out1.y / out1.w - ray->origin.y;
	ray->direction.z = out1.z / out1.w - ray->origin.z;

	return true;
}