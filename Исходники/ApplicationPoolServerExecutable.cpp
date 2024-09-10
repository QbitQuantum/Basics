	void processGet(const vector<string> &args) {
		TRACE_POINT();
		Application::SessionPtr session;
		bool failed = false;
		
		try {
			session = server.pool.get(SpawnOptions(
				args[1], args[2] == "true", args[3],
				args[4], args[5], args[6],
				atoi(args[7]), atoi(args[8])));
			sessions[lastSessionID] = session;
			lastSessionID++;
		} catch (const SpawnException &e) {
			UPDATE_TRACE_POINT();
			this_thread::disable_syscall_interruption dsi;
			
			if (e.hasErrorPage()) {
				P_TRACE(3, "Client " << this << ": SpawnException "
					"occured (with error page)");
				channel.write("SpawnException", e.what(), "true", NULL);
				channel.writeScalar(e.getErrorPage());
			} else {
				P_TRACE(3, "Client " << this << ": SpawnException "
					"occured (no error page)");
				channel.write("SpawnException", e.what(), "false", NULL);
			}
			failed = true;
		} catch (const BusyException &e) {
			UPDATE_TRACE_POINT();
			this_thread::disable_syscall_interruption dsi;
			channel.write("BusyException", e.what(), NULL);
			failed = true;
		} catch (const IOException &e) {
			UPDATE_TRACE_POINT();
			this_thread::disable_syscall_interruption dsi;
			channel.write("IOException", e.what(), NULL);
			failed = true;
		}
		UPDATE_TRACE_POINT();
		if (!failed) {
			this_thread::disable_syscall_interruption dsi;
			try {
				UPDATE_TRACE_POINT();
				channel.write("ok", toString(session->getPid()).c_str(),
					toString(lastSessionID - 1).c_str(), NULL);
				channel.writeFileDescriptor(session->getStream());
				session->closeStream();
			} catch (const exception &) {
				UPDATE_TRACE_POINT();
				P_TRACE(3, "Client " << this << ": something went wrong "
					"while sending 'ok' back to the client.");
				sessions.erase(lastSessionID - 1);
				throw;
			}
		}
	}