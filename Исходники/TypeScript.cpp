CTypeScript::CTypeScript() : m_ref(1)
{
	InterlockedIncrement(&ulLockCount);

	CLSID CLSID_Script;
	CLSIDFromProgID(L"JScript", &CLSID_Script);

	CoCreateInstance(CLSID_Script, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_js));
}