int main(int argc, char **argv)
{
	GlutApp* app = new DemoRegularConvexGen();

	app->initGlut(argc, argv);
	app->setTitle("test Regular convex generator\n");
	app->setWindowsSize(600, 600);

	app->setTimer(1000, 100);

	app->run();

	return 0;
}