void BURGER_API Burger::OSCursorImage::Shutdown(void)
{
	if (m_pCursorImage) {
		DestroyCursor(m_pCursorImage);
		m_pCursorImage = NULL;
	}
}