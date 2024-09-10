void DllInterface::UnInitialize()
{
	FreeLibrary(m_hinst);
	m_the_app.DllUnInitialize();
}