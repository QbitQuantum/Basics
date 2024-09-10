int main(int argc, char* argv[])
{
	App app;
	app.init();
	app.run();
	app.shutdown();
	return app.getExitCode();
}