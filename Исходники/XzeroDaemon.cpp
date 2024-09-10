/** starts new binary with (new) config - as child process, and gracefully shutdown self.
 */
void XzeroDaemon::reexec()
{
	if (state_ != XzeroState::Running) {
		server_->log(x0::Severity::info, "Reexec requested again?. Ignoring.");
		return;
	}

	eventHandler_->setState(XzeroState::Upgrading);

	// suspend worker threads while performing the reexec
	for (x0::HttpWorker* worker: server_->workers()) {
		worker->suspend();
	}

	x0::Buffer serializedListeners;

	for (x0::ServerSocket* listener: server_->listeners()) {
		// stop accepting new connections
		listener->stop();

		// and clear O_CLOEXEC on listener socket, as we want to probably resume these listeners in the child process
		listener->setCloseOnExec(false);

		serializedListeners.push_back(listener->serialize());
		serializedListeners.push_back(';');
	}

	server_->log(x0::Severity::debug, "Setting envvar XZERO_LISTEN_FDS to: '%s'", serializedListeners.c_str());
	setenv("XZERO_LISTEN_FDS", serializedListeners.c_str(), true);

	// prepare environment for new binary
	char sgen[20];
	snprintf(sgen, sizeof(sgen), "%u", server_->generation());
	setenv("XZERO_UPGRADE", sgen, true);

	std::vector<const char*> args;
	args.push_back(argv_[0]);

	if (systemd_)
		args.push_back("--systemd");

	if (!instant_.empty()) {
		args.push_back("--instant");
		args.push_back(instant_.c_str());
	} else {
		args.push_back("-f");
		args.push_back(configfile_.c_str());
	}

	args.push_back("--log-target");
	args.push_back(logTarget_.c_str());

	if (!logFile_.empty() && instant_.empty()) {
		args.push_back("--log-file");
		args.push_back(logFile_.c_str());
	}

	args.push_back("--log-severity");
	char logLevel[16];
	snprintf(logLevel, sizeof(logLevel), "%d", static_cast<int>(logLevel_));
	args.push_back(logLevel);

	if (!pidfile_.empty()) {
		args.push_back("--pid-file");
		args.push_back(pidfile_.c_str());
	}

	args.push_back("--no-fork"); // we never fork (potentially again)
	args.push_back(nullptr);

	int childPid = vfork();
	switch (childPid) {
		case 0:
			// in child
			execve(argv_[0], (char**)args.data(), environ);
			server_->log(x0::Severity::error, "Executing new child process failed: %s", strerror(errno));
			abort();
			break;
		case -1:
			// error
			server_->log(x0::Severity::error, "Forking for new child process failed: %s", strerror(errno));
			break;
		default:
			// in parent
			// the child process must tell us whether to gracefully shutdown or to resume.
			eventHandler_->setupChild(childPid);

			// we lost ownership of the PID file, if we had one as the child overwrites it.
			pidfile_ = "";

			// FIXME do we want a reexecTimeout, to handle possible cases where the child is not calling back? to kill them, if so!
			break;
	}

	// continue running the the process (with listeners disabled)
	server_->log(x0::Severity::debug, "Setting O_CLOEXEC on listener sockets");
	for (auto listener: server_->listeners()) {
		listener->setCloseOnExec(true);
	}
}