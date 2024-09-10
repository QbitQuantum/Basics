int
main(int argc, char *argv[]) {
	disableOomKiller();
	
	agentsOptions = initializeAgent(argc, argv, "PassengerWatchdog");
	logLevel      = agentsOptions.getInt("log_level");
	webServerPid  = agentsOptions.getPid("web_server_pid");
	tempDir       = agentsOptions.get("temp_dir");
	userSwitching = agentsOptions.getBool("user_switching");
	defaultUser   = agentsOptions.get("default_user");
	defaultGroup  = agentsOptions.get("default_group");
	webServerWorkerUid = agentsOptions.getUid("web_server_worker_uid");
	webServerWorkerGid = agentsOptions.getGid("web_server_worker_gid");
	passengerRoot = agentsOptions.get("passenger_root");
	rubyCommand   = agentsOptions.get("ruby");
	maxPoolSize        = agentsOptions.getInt("max_pool_size");
	maxInstancesPerApp = agentsOptions.getInt("max_instances_per_app");
	poolIdleTime       = agentsOptions.getInt("pool_idle_time");
	serializedPrestartURLs  = agentsOptions.get("prestart_urls");
	
	try {
		randomGenerator = new RandomGenerator();
		errorEvent = new EventFd();
		
		MessageChannel feedbackChannel(FEEDBACK_FD);
		serverInstanceDir.reset(new ServerInstanceDir(webServerPid, tempDir));
		generation = serverInstanceDir->newGeneration(userSwitching, defaultUser,
			defaultGroup, webServerWorkerUid, webServerWorkerGid);
		agentsOptions.set("server_instance_dir", serverInstanceDir->getPath());
		agentsOptions.setInt("generation_number", generation->getNumber());
		
		ServerInstanceDirToucher serverInstanceDirToucher;
		ResourceLocator resourceLocator(passengerRoot);
		if (agentsOptions.get("analytics_server", false).empty()) {
			// Using local, server instance specific logging agent.
			loggingAgentAddress  = "unix:" + generation->getPath() + "/logging.socket";
			loggingAgentPassword = randomGenerator->generateAsciiString(64);
		} else {
			// Using remote logging agent.
			loggingAgentAddress = agentsOptions.get("analytics_server");
		}
		
		HelperAgentWatcher helperAgentWatcher(resourceLocator);
		LoggingAgentWatcher loggingAgentWatcher(resourceLocator);
		
		vector<AgentWatcher *> watchers;
		vector<AgentWatcher *>::iterator it;
		watchers.push_back(&helperAgentWatcher);
		if (agentsOptions.get("analytics_server", false).empty()) {
			watchers.push_back(&loggingAgentWatcher);
		}
		
		for (it = watchers.begin(); it != watchers.end(); it++) {
			try {
				(*it)->start();
			} catch (const std::exception &e) {
				feedbackChannel.write("Watchdog startup error",
					e.what(), NULL);
				forceAllAgentsShutdown(watchers);
				return 1;
			}
			// Allow other exceptions to propagate and crash the watchdog.
		}
		for (it = watchers.begin(); it != watchers.end(); it++) {
			try {
				(*it)->startWatching();
			} catch (const std::exception &e) {
				feedbackChannel.write("Watchdog startup error",
					e.what(), NULL);
				forceAllAgentsShutdown(watchers);
				return 1;
			}
			// Allow other exceptions to propagate and crash the watchdog.
		}
		
		feedbackChannel.write("Basic startup info",
			serverInstanceDir->getPath().c_str(),
			toString(generation->getNumber()).c_str(),
			NULL);
		
		for (it = watchers.begin(); it != watchers.end(); it++) {
			(*it)->sendStartupInfo(feedbackChannel);
		}
		
		feedbackChannel.write("All agents started", NULL);
		
		this_thread::disable_interruption di;
		this_thread::disable_syscall_interruption dsi;
		bool exitGracefully = waitForStarterProcessOrWatchers(watchers);
		AgentWatcher::stopWatching(watchers);
		if (exitGracefully) {
			/* Fork a child process which cleans up all the agent processes in
			 * the background and exit this watchdog process so that we don't block
			 * the web server.
			 */
			cleanupAgentsInBackground(watchers);
			return 0;
		} else {
			P_DEBUG("Web server did not exit gracefully, forcing shutdown of all service processes...");
			forceAllAgentsShutdown(watchers);
			return 1;
		}
	} catch (const tracable_exception &e) {
		P_ERROR(e.what() << "\n" << e.backtrace());
		return 1;
	} catch (const std::exception &e) {
		P_ERROR(e.what());
		return 1;
	}
}