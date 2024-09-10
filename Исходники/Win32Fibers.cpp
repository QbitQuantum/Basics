	void rawCorSwitchToFiber(void *fiber)
	{
#if defined(CORHOST)
		DWORD *cookie;
		corhost->SwitchOutLogicalThreadState(&cookie);
#endif
		SwitchToFiber(fiber);
#if defined(CORHOST)
		corhost->SwitchInLogicalThreadState(cookie);
#endif
	}