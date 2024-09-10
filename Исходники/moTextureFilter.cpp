void moHueSatIntMatrix::Update(MOfloat p_int, MOfloat p_sat, MOfloat p_hue)
{
	m_int = m_min_int + p_int * (m_max_int - m_min_int);
	m_sat = m_min_sat + p_sat * (m_max_sat - m_min_sat);
	m_hue = m_min_hue + p_hue * (m_max_hue - m_min_hue);

	m_int = momax(1e-3, m_int);

	IdentityMatrix();
	IntensityMatrix();
	SaturateMatrix();
	if (m_PreserveLuminance) HueRotateMatrix();
	else SimpleHueRotateMatrix();
}