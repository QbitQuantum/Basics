int main(int argc, char* argv[])
{
	// Setup bad allocation handler
	std::set_new_handler(badAllocationHandler);

#ifndef _WIN32
	// ignore sigpipe...
	struct sigaction sigh;
	sigh.sa_handler = SIG_IGN;
	sigh.sa_flags = 0;
	sigemptyset(&sigh.sa_mask);
	sigaction(SIGPIPE, &sigh, nullptr);
#endif

	ServiceManager servicer;

	g_dispatcher.start();
	g_scheduler.start();

	g_dispatcher.addTask(createTask(std::bind(mainLoader, argc, argv, &servicer)));

	g_loaderSignal.wait(g_loaderUniqueLock);

	if (servicer.is_running()) {
		std::cout << ">> " << g_config.getString(ConfigManager::SERVER_NAME) << " Server Online!" << std::endl << std::endl;
#ifdef _WIN32
		SetConsoleCtrlHandler([](DWORD) -> BOOL {
			g_dispatcher.addTask(createTask([]() {
				g_dispatcher.addTask(createTask(
					std::bind(&Game::shutdown, &g_game)
				));
				g_scheduler.stop();
				g_databaseTasks.stop();
				g_dispatcher.stop();
			}));
			ExitThread(0);
		}, 1);
#endif
		servicer.run();
		g_scheduler.join();
		g_databaseTasks.join();
		g_dispatcher.join();
	} else {
		std::cout << ">> No services running. The server is NOT online." << std::endl;
		g_dispatcher.addTask(createTask([]() {
			g_dispatcher.addTask(createTask([]() {
				g_scheduler.shutdown();
				g_databaseTasks.shutdown();
				g_dispatcher.shutdown();
			}));
			g_scheduler.stop();
			g_databaseTasks.stop();
			g_dispatcher.stop();
		}));
		g_scheduler.join();
		g_databaseTasks.join();
		g_dispatcher.join();
	}
	return 0;
}