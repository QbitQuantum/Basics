int main(int argc __attribute__((unused)), char *argv[])
{
	int status = 0;

	setlocale(LC_ALL, getenv(ENV_LANG));
	textdomain("mines");

	// Only work in graphics mode
	if (!graphicsAreEnabled())
	{
		printf(_("\nThe \"%s\" command only works in graphics mode\n"),
			argv[0]);
		return (errno = ERR_NOTINITIALIZED);
	}

	// Load our images
	status = imageLoad(MINE_IMAGE, 0, 0, &mineImage);
	if (status < 0)
	{
		printf(_("\nCan't load %s\n"), MINE_IMAGE);
		return (errno = status);
	}
	mineImage.transColor.green = 255;

	// Create a new window
	window = windowNew(multitaskerGetCurrentProcessId(), WINDOW_TITLE);

	// Register an event handler to catch window events.
	windowRegisterEventHandler(window, &eventHandler);

	// Generate mine field
	initialize();

	// Go live.
	windowSetVisible(window, 1);

	// Run the GUI
	windowGuiRun();

	// Destroy the window
	windowDestroy(window);

	imageFree(&mineImage);

	// Done
	return (0);
}