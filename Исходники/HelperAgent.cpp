int
main(int argc, char *argv[]) {
	TRACE_POINT();
	VariantMap options = initializeAgent(argc, argv, "PassengerHelperAgent");
	pid_t   webServerPid  = options.getPid("web_server_pid");
	string  tempDir       = options.get("temp_dir");
	bool    userSwitching = options.getBool("user_switching");
	string  defaultUser   = options.get("default_user");
	string  defaultGroup  = options.get("default_group");
	string  passengerRoot = options.get("passenger_root");
	string  rubyCommand   = options.get("ruby");
	unsigned int generationNumber   = options.getInt("generation_number");
	unsigned int maxPoolSize        = options.getInt("max_pool_size");
	unsigned int maxInstancesPerApp = options.getInt("max_instances_per_app");
	unsigned int poolIdleTime       = options.getInt("pool_idle_time");
	
	try {
		UPDATE_TRACE_POINT();
		Server server(FEEDBACK_FD, webServerPid, tempDir,
			userSwitching, defaultUser, defaultGroup,
			passengerRoot, rubyCommand, generationNumber,
			maxPoolSize, maxInstancesPerApp, poolIdleTime,
			options);
		
		UPDATE_TRACE_POINT();
		server.mainLoop();
	} catch (const tracable_exception &e) {
		P_ERROR(e.what() << "\n" << e.backtrace());
		return 1;
	} catch (const std::exception &e) {
		P_ERROR(e.what());
		return 1;
	} catch (...) {
		P_ERROR("Unknown exception thrown in main thread.");
		throw;
	}
	
	return 0;
}