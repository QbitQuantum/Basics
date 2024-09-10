CEGControlBar::~CEGControlBar(void)
{
	if( NULL != m_curHorzDrag )
		DestroyCursor( m_curHorzDrag );
	if( NULL != m_curVertDrag )
		DestroyCursor( m_curVertDrag );
}