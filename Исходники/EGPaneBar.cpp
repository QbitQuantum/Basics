CEGPaneBar::~CEGPaneBar(void)
{
	if( NULL != m_curHorzDrag )
		DestroyCursor( m_curHorzDrag );
	if( NULL != m_curVertDrag )
		DestroyCursor( m_curVertDrag );
	if( NULL != m_pszCaption )
		free( m_pszCaption );
	if( NULL != m_fntCaption )
		DeleteObject( m_fntCaption );
	if( NULL != m_fntXButton )
		DeleteObject( m_fntXButton );
}