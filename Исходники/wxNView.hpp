	virtual void OnLeftUp(wxMouseEvent& /*event*/)
	{
		SetCursor(m_handOpenCursor);
		m_handToolActive = false;
	}