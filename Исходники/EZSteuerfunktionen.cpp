double Steuerfunktionen::geschwindigkeit( double d ) const
{
	if (m_geschwindigkeitFunktion == NULL)
		return NaN();
	return (*m_geschwindigkeitFunktion)(d);
}