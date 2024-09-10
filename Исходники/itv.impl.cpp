void Nena::InteractiveTV::Web::View::Initialize(
	Nena::Application::Window *window, 
	Session *session
	)
{
	::BOOL status;
	::DEVMODEA screen;
	::Nena::Platform::ZeroValue(&screen);

	ZeroMemory(&screen, sizeof DEVMODEA);
	status = EnumDisplaySettingsA(nullptr, ENUM_CURRENT_SETTINGS, &screen);
	dims.u32[0] = (uint32) screen.dmPelsWidth;
	dims.u32[1] = (uint32) screen.dmPelsHeight;

	impl->Initialize(
		core->impl,		// web core
		dims.u32[0],	// screen width
		dims.u32[1],	// screen height
		session->impl	// session config
		);
}