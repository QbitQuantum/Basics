	void UnloadSmiley(void)
	{
		regAniSmileys.remove(this);

		if (timerId && (timerId+1) && regAniSmileys.getCount() == 0) {
			KillTimer(NULL, timerId);
			timerId = 0;
		}
		if (m_img) m_img->Release();
		m_img = NULL;
	}