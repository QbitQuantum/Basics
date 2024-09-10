void CBeam::InputColorRedValue( inputdata_t &inputdata )
{
	int nNewColor = clamp( inputdata.value.Int(), 0, 255 );
	SetColor( nNewColor, m_clrRender->g, m_clrRender->b );
}