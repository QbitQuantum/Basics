	void LoadSIMDState()
	{
		_mm_setcsr(saved_sse_state);
	}