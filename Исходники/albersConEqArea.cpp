void AlbersConEqArea::_inverse(double x, double y)
{
	double rh1;			/* height above ellipsoid	*/
	double qs;			/* function q			*/
	double con;			/* temporary sign value		*/
	double theta;			/* angle			*/
	long   flag;			/* error flag;			*/
	
	flag = 0;
	x -= m_falseEasting;
	y = m_rh - y + m_falseNorthing;;
	
	if (m_ns0 >= 0)
	{
		rh1 = sqrt(x * x + y * y);
		con = 1.0;
    }
	
	else
	{
		rh1 = -sqrt(x * x + y * y);
		con = -1.0;
	}

	theta = 0.0;
	if (rh1 != 0.0)
		theta = atan2(con * x, con * y);
	
	con = rh1 * m_ns0 / m_rMajor;
	qs = (m_c - con * con) / m_ns0;
	
	if (m_e >= 1e-10)
	{
		con = 1 - .5 * (1.0 - m_es) * log((1.0 - m_e) / (1.0 + m_e))/m_e;
		if (fabs(fabs(con) - fabs(qs)) > .0000000001 )
		{
			m_latitude = Util::phi1z(m_e,qs,&flag);
			if (flag != 0) {
				setError(flag);
				return;
			}
		}

		else
	
		{
		 if (qs >= 0)
			m_latitude = .5 * PI;
		 else
			m_latitude = -.5 * PI;
		}
	}
	
	else
	{
		m_latitude = Util::phi1z(m_e,qs,&flag);
		if (flag != 0) {
			setError(flag);
			return;
		}
    }

	m_longitude = Util::adjust_lon(theta/m_ns0 + m_centerLon);

}