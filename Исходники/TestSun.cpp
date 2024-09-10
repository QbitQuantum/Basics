int main(int argc, char** argv)
{
	GlutApp* app = new TestSun();

	app->initGlut(argc, argv);
	app->setTitle("Timer test");
	app->setWindowsSize(640, 480);

	app->setTimer(1000, 20);

	app->run();

	return 0;
}