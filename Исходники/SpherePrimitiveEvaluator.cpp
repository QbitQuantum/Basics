/// Implementation derived from Wild Magic (Version 2) Software Library, available
/// from http://www.geometrictools.com/Downloads/WildMagic2p5.zip under free license
bool SpherePrimitiveEvaluator::intersectionPoint( const Imath::V3f &origin, const Imath::V3f &direction,
	PrimitiveEvaluator::Result *result, float maxDistance ) const
{
	assert( dynamic_cast<Result *>( result ) );

	Result *sr = static_cast<Result *>( result );

	Imath::V3f dir = direction.normalized();
	(void)direction;
	float a0 = origin.dot( origin ) - m_sphere->radius() * m_sphere->radius();
	float a1 = dir.dot( origin );
	float discr = a1 * a1 - a0;

	if (discr < 0.0)
	{
		return false;
	}

	if ( discr >= Imath::limits<float>::epsilon() )
	{
		float root = sqrt( discr );
		float t0 = -a1 - root;
		float t1 = -a1 + root;

		Imath::V3f p0 = origin + t0 * dir;
		Imath::V3f p1 = origin + t1 * dir;

		if ( t0 >= 0.0 )
		{
			if ( t1 >= 0.0 )
			{
				if ( (origin - p0).length2() < ( origin - p1 ).length2() )
				{
					sr->m_p = p0;
				}
				else
				{
					sr->m_p = p1;
				}
			}
			else
			{
				sr->m_p = p0;
			}
		}
		else if ( t1 >= 0.0 )
		{
			sr->m_p = p1;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float t = -a1;

		if ( t >= 0.0 )
		{
			sr->m_p = origin + t * dir;
		}
		else
		{
			return false;
		}
	}

	if ( (sr->m_p - origin).length() < maxDistance)
	{
		return true;
	}

	return false;
}