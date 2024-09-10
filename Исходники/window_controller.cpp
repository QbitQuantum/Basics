static void RestoreVideoSettings()
{
	sht::Application * app = sht::Application::GetInstance();
	if (app->fullscreen())
	{
		ChangeDisplaySettingsA(NULL, 0);
	}
}