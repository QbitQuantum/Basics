void CAnimMixer::processScroll(sInt cursorX, sBool scrollDirect)
{
	sInt oldStartPixel = m_startPixel;

	if (scrollDirect)
		m_startPixel = fr::maximum(0, m_startPixel + cursorX);
	else
	{
		sInt scrollDelta = m_scrlPoint.x - cursorX;
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
			scrollDelta *= 8;

		m_startPixel = fr::maximum(0, m_startPixel + scrollDelta);
		m_scrlPoint.x = cursorX;
	}

  RECT rc;
  GetClientRect(&rc);
	rc.top = 24; // where the buttons end

  ScrollWindow(oldStartPixel - m_startPixel, 0, &rc, &rc);
	m_timeBarPos += oldStartPixel - m_startPixel;

  UpdateWindow();
}