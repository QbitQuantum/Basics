/*
 * Animate to the rpgcode screen (for RPGCode functions).
 */
void CAnimation::animate(const int x, const int y)
{
	extern CCanvas *g_cnvRpgCode;
	extern void processEvent();

	// Copy the screen.
	const CCanvas cnvScr = *g_cnvRpgCode;

	std::vector<CCanvas *>::iterator i = m_canvases.begin(), start = i;
	for (; i != m_canvases.end(); ++i)
	{
		if (!*i)
		{
			*i = new CCanvas();
			(*i)->CreateBlank(NULL, m_data.pxWidth, m_data.pxHeight, TRUE);
			if (!(this->*renderFrame)(*i, i - start)) continue;
		}

		// Place on g_cnvRpgCode.
		(*i)->BltTransparent(g_cnvRpgCode, x, y, TRANSP_COLOR);

		// Refresh the screen.
		processEvent();
		renderRpgCodeScreen();

		// Play the frame's sound.
		playFrameSound(i - start);

		Sleep(DWORD(m_data.delay * MILLISECONDS));

		// Replace g_cnvRpgCode with the original.
		cnvScr.BltPart(
			g_cnvRpgCode, 
			x, y, 
			x, y, 
			m_data.pxWidth, m_data.pxHeight,
			SRCCOPY
		);
	}
}