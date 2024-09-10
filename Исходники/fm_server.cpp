void *ServerThread::run()
{
	DSTACK(FUNCTION_NAME);
	BEGIN_DEBUG_EXCEPTION_HANDLER

	f32 dedicated_server_step = g_settings->getFloat("dedicated_server_step");
	m_server->AsyncRunStep(0.1, true);

	auto time = porting::getTimeMs();
	while (!stopRequested()) {
		try {
			m_server->getEnv().getMap().getBlockCacheFlush();
			u32 time_now = porting::getTimeMs();
			{
			TimeTaker timer("Server AsyncRunStep()");
			m_server->AsyncRunStep((time_now - time)/1000.0f);
			}
			time = time_now;

			TimeTaker timer("Server Receive()");
			// Loop used only when 100% cpu load or on old slow hardware.
			// usually only one packet recieved here
			u32 end_ms = porting::getTimeMs();
			int sleep = (1000 * dedicated_server_step) - (end_ms - time_now);
			auto sleep_min = m_server->overload ? 1000 : 50;
			if (sleep < sleep_min)
				sleep = sleep_min;
			end_ms += sleep; //u32(1000 * dedicated_server_step/2);
			for (u16 i = 0; i < 1000; ++i) {
				if (!m_server->Receive(sleep)) {
					//errorstream<<"Server: Recieve nothing="  << i << " per="<<porting::getTimeMs()-(end_ms-sleep)<<" sleep="<<sleep<<std::endl;
					break;
				}
				if (i > 50 && porting::getTimeMs() > end_ms) {
					//verbosestream<<"Server: Recieve queue overloaded: processed="  << i << " per="<<porting::getTimeMs()-(end_ms-sleep)<<" sleep="<<sleep << " eventssize=" << m_server->m_con.events_size()<<std::endl;
					break;
				}
			}
			auto events = m_server->m_con.events_size();
			if (events) {
				g_profiler->add("Server: Queue", events);
			}
			if (events > 500) {
				if (!m_server->overload)
					errorstream<<"Server: Enabling overload mode queue=" << events << "\n";
				if (m_server->overload < events)
					m_server->overload = events;
			} else {
				if (m_server->overload)
					errorstream<<"Server: Disabling overload mode queue=" << events << "\n";
				m_server->overload = 0;
			}
		} catch (con::NoIncomingDataException &e) {
			//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		} catch (con::PeerNotFoundException &e) {
			infostream<<"Server: PeerNotFoundException"<<std::endl;
		} catch (ClientNotFoundException &e) {
		} catch (con::ConnectionBindFailed &e) {
			m_server->setAsyncFatalError(e.what());
#if !EXEPTION_DEBUG
		} catch (LuaError &e) {
			m_server->setAsyncFatalError("Lua: " + std::string(e.what()));
		} catch (std::exception &e) {
			errorstream << m_name << ": exception: "<<e.what()<<std::endl;
		} catch (...) {
			errorstream << m_name << ": Ooops..."<<std::endl;
#endif
		}
	}

	END_DEBUG_EXCEPTION_HANDLER

	return NULL;
}