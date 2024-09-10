int main(int argc, char* argv[])
{
	Lumix::setCommandLine(argc, argv);
	App app;
	app.init();
	app.run();
	app.shutdown();
	return app.getExitCode();
}