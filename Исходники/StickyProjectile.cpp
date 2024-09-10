void CStickyProjectile::CalculateLocationForStick( const IEntity& projectile, const Vec3& collPos, const Vec3& collNormal, QuatT& outLocation ) const
{
	if(m_flags&eSF_OrientateToCollNormal)
	{
		const float bigz = cry_fabsf(collNormal.z)-cry_fabsf(collNormal.y);
		const Vec3 temp(0.f,(float)__fsel(bigz,1.f,0.f),(float)__fsel(bigz,0.f,1.f));
		outLocation.q = Quat(Matrix33::CreateOrientation( temp.Cross(collNormal), -collNormal, 0));

		AABB aabb;
		projectile.GetLocalBounds(aabb);
		outLocation.t = collPos + (outLocation.q.GetColumn2() * ((aabb.max.y-aabb.min.y)*0.5f));
	}
	else
	{
		outLocation.q = projectile.GetRotation();
		outLocation.t = collPos + (outLocation.q.GetColumn1() * 0.1f);
	}
}