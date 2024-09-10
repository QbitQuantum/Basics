Matrix3& Matrix3::PerspectiveRH( const Real fov, const Real aspect, const Real zn, const Real zf )
{
#ifdef __USE_D3DX__
	D3DXMatrixPerspectiveFovRH( (D3DXMATRIX*)this, fov, aspect, zn, zf );
#else
	Real h = 1.0f / TAN( fov * 0.5f );
	Real w = h / aspect;
	Real Q = zf / ( zn - zf );

	Zero();
		
	e[0] = w;
	e[5] = h;
	e[10] = Q;
	e[14] = Q * zn;
	e[11] = -1.0;
		
#endif
	return *this;
}