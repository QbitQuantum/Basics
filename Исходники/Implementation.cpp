void
Group::detachedProcessesCheckerMain(GroupPtr self) {
	TRACE_POINT();
	Pool *pool = getPool();

	Pool::DebugSupportPtr debug = pool->debugSupport;
	if (debug != NULL && debug->detachedProcessesChecker) {
		debug->debugger->send("About to start detached processes checker");
		debug->messages->recv("Proceed with starting detached processes checker");
	}

	boost::unique_lock<boost::mutex> lock(pool->syncher);
	while (true) {
		assert(detachedProcessesCheckerActive);

		if (getLifeStatus() == SHUT_DOWN || this_thread::interruption_requested()) {
			UPDATE_TRACE_POINT();
			P_DEBUG("Stopping detached processes checker");
			detachedProcessesCheckerActive = false;
			break;
		}

		UPDATE_TRACE_POINT();
		if (!detachedProcesses.empty()) {
			P_TRACE(2, "Checking whether any of the " << detachedProcesses.size() <<
				" detached processes have exited...");
			ProcessList::iterator it, end = detachedProcesses.end();
			ProcessList processesToRemove;

			for (it = detachedProcesses.begin(); it != end; it++) {
				const ProcessPtr process = *it;
				switch (process->getLifeStatus()) {
				case Process::ALIVE:
					if (process->canTriggerShutdown()) {
						P_DEBUG("Detached process " << process->inspect() <<
							" has 0 active sessions now. Triggering shutdown.");
						process->triggerShutdown();
						assert(process->getLifeStatus() == Process::SHUTDOWN_TRIGGERED);
					}
					break;
				case Process::SHUTDOWN_TRIGGERED:
					if (process->canCleanup()) {
						P_DEBUG("Detached process " << process->inspect() << " has shut down. Cleaning up associated resources.");
						process->cleanup();
						assert(process->getLifeStatus() == Process::DEAD);
						processesToRemove.push_back(process);
					} else if (process->shutdownTimeoutExpired()) {
						P_WARN("Detached process " << process->inspect() <<
							" didn't shut down within " PROCESS_SHUTDOWN_TIMEOUT_DISPLAY
							". Forcefully killing it with SIGKILL.");
						kill(process->getPid(), SIGKILL);
					}
					break;
				default:
					P_BUG("Unknown 'lifeStatus' state " << (int) process->getLifeStatus());
				}
			}

			UPDATE_TRACE_POINT();
			end = processesToRemove.end();
			for (it = processesToRemove.begin(); it != end; it++) {
				removeProcessFromList(*it, detachedProcesses);
			}
		}

		UPDATE_TRACE_POINT();
		if (detachedProcesses.empty()) {
			UPDATE_TRACE_POINT();
			P_DEBUG("Stopping detached processes checker");
			detachedProcessesCheckerActive = false;

			boost::container::vector<Callback> actions;
			if (shutdownCanFinish()) {
				UPDATE_TRACE_POINT();
				finishShutdown(actions);
			}

			verifyInvariants();
			verifyExpensiveInvariants();
			lock.unlock();
			UPDATE_TRACE_POINT();
			runAllActions(actions);
			break;
		} else {
			UPDATE_TRACE_POINT();
			verifyInvariants();
			verifyExpensiveInvariants();
		}

		// Not all processes can be shut down yet. Sleep for a while unless
		// someone wakes us up.
		UPDATE_TRACE_POINT();
		detachedProcessesCheckerCond.timed_wait(lock,
			posix_time::milliseconds(100));
	}
}