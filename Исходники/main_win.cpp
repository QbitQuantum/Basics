INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	App app;
	app.init();
	app.run();
	app.shutdown();
	return app.getExitCode();
}