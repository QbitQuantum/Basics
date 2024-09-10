AcceleratorHook::~AcceleratorHook(){
	UnhookWindowsHookEx(m_Hook);

	DeleteCriticalSection(&m_CriticalSection);
}