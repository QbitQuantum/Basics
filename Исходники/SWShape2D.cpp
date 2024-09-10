void SWCircleShape2D::computeAABB( taabb2d& aabb, const tmat33& mat ) const
{
	aabb.lower = tvec2( FLT_MAX, FLT_MAX );
	aabb.upper = -aabb.lower;

	tmat33 inv;
	mat.inverse( inv );

	const tuint count = 4;
	tvec2 dirs[count] = { tvec2::axisX, tvec2::axisY, -tvec2::axisX, -tvec2::axisY };
	for ( tuint i = 0 ; i < count ; ++i )
	{
		tvec2 localDIr = (tvec3(dirs[i],0) * inv).xy().normal();
		tvec2 point = (localDIr * m_radius) + m_center;

		point = point * mat;
		aabb.min( point );
		aabb.max( point );
	}
}