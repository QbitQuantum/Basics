//==============================================================================
Bool Gjk::update(const Support& a)
{
	if(m_count == 2)
	{
		Vec4 ao = -a.m_v;

		// Compute the vectors parallel to the edges we'll test
		Vec4 ab = m_simplex[1].m_v - a.m_v;
		Vec4 ac = m_simplex[2].m_v - a.m_v;

		// Compute the triangle's normal
		Vec4 abc = ab.cross(ac);

		// Compute a vector within the plane of the triangle,
		// Pointing away from the edge ab
		Vec4 abp = ab.cross(abc);

		if(abp.dot(ao) > 0.0)
		{
			// The origin lies outside the triangle, near the edge ab
			m_simplex[2] = m_simplex[1];
			m_simplex[1] = a;

			m_dir = crossAba(ab, ao);

			return false;
		}

		// Perform a similar test for the edge ac
		Vec4 acp = abc.cross(ac);

		if(acp.dot(ao) > 0.0)
		{
			m_simplex[1] = a;
			m_dir = crossAba(ac, ao);

			return false;
		}

		// If we get here, then the origin must be within the triangle,
		// but we care whether it is above or below it, so test
		if(abc.dot(ao) > 0.0)
		{
			m_simplex[3] = m_simplex[2];
			m_simplex[2] = m_simplex[1];
			m_simplex[1] = a;

			m_dir = abc;
		}
		else
		{
			m_simplex[3] = m_simplex[1];
			m_simplex[1] = a;

			m_dir = -abc;
		}

		m_count = 3;

		// Again, need a tetrahedron to enclose the origin
		return false;
	}
	else if(m_count == 3)
	{
		Vec4 ao = -a.m_v;

		Vec4 ab = m_simplex[1].m_v - a.m_v;
		Vec4 ac = m_simplex[2].m_v - a.m_v;

		Vec4 abc = ab.cross(ac);

		Vec4 ad, acd, adb;

		if(abc.dot(ao) > 0.0)
		{
			// In front of triangle ABC
			goto check_face;
		}

		ad = m_simplex[3].m_v - a.m_v;
		acd = ac.cross(ad);

		if(acd.dot(ao) > 0.0)
		{
			// In front of triangle ACD
			m_simplex[1] = m_simplex[2];
			m_simplex[2] = m_simplex[3];

			ab = ac;
			ac = ad;

			abc = acd;
			goto check_face;
		}

		adb = ad.cross(ab);

		if(adb.dot(ao) > 0.0)
		{
			// In front of triangle ADB

			m_simplex[2] = m_simplex[1];
			m_simplex[1] = m_simplex[3];

			ac = ab;
			ab = ad;

			abc = adb;
			goto check_face;
		}

		// Behind all three faces, the origin is in the tetrahedron, we're done
		m_simplex[0] = a;
		m_count = 4;
		return true;

	check_face:

		// We have a CCW wound triangle ABC
		// the point is in front of this triangle
		// it is NOT "below" edge BC
		// it is NOT "above" the plane through A that's parallel to BC
		Vec4 abp = ab.cross(abc);

		if(abp.dot(ao) > 0.0)
		{
			m_simplex[2] = m_simplex[1];
			m_simplex[1] = a;

			m_dir = crossAba(ab, ao);

			m_count = 2;
			return false;
		}

		Vec4 acp = abc.cross(ac);

		if(acp.dot(ao) > 0.0)
		{
			m_simplex[1] = a;

			m_dir = crossAba(ac, ao);

			m_count = 2;
			return false;
		}

		m_simplex[3] = m_simplex[2];
		m_simplex[2] = m_simplex[1];
		m_simplex[1] = a;

		m_dir = abc;
		m_count = 3;

		return false;
	}

	ANKI_ASSERT(0);
	return true;
}