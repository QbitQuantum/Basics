//ÆôÓÃ¡¢¹Ø±ÕÊäÈë·¨
void CIme::EnableIme( bool bEnable )
{ 
	if( m_bEnableIme == bEnable )
		return;

	ImmAssociateContext( m_hWnd, bEnable ? m_hImc : NULL );
	m_bEnableIme = bEnable;
}