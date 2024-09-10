float AutomatableModel::fittedValue( float value ) const
{
	value = tLimit<float>( value, m_minValue, m_maxValue );

	if( m_step != 0 )
	{
		value = nearbyintf( value / m_step ) * m_step;
	}

	roundAt( value, m_maxValue );
	roundAt( value, m_minValue );
	roundAt( value, 0.0f );

	if( value < m_minValue )
	{
		return m_minValue;
	}
	else if( value > m_maxValue )
	{
		return m_maxValue;
	}

	return value;
}