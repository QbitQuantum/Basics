/*
* Service Main function - Called by the SCM after the service has started
*/
void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
	gServiceHandle = RegisterServiceCtrlHandler(g_serviceName, ServiceCtrlHandler);
	if (gServiceHandle == 0)
	{
		logStartError("RegisterServiceCtrlHandler failed.");
	}
	else
	{
		// signal service is starting
		setServiceStatus(SERVICE_START_PENDING, TRUE, NO_ERROR, 3000);

		// create event for when service is signaled to stop
		g_serviceStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		if (g_serviceStopEvent)
		{
			TCHAR szPath[MAX_PATH];
			char *last_slash;

			GetModuleFileName(NULL, szPath, MAX_PATH);
			last_slash = s_strrchr(szPath, '\\', MAX_PATH);
			if (NULL != last_slash)
				*last_slash = '\0';

			if (SetCurrentDirectory(szPath))
			{
				std::vector<monitor::NvmMonitorBase *> monitors;
				monitor::NvmMonitorBase::getMonitors(monitors);

				size_t handleCount = monitors.size() + 1; // +1 to also add g_serviceStopEvent
				HANDLE handles[handleCount];
				for (size_t i = 0; i < monitors.size(); i++)
				{
					handles[i] =
							CreateThread(NULL, 0, WorkerThread, (LPVOID) (monitors[i]), 0, NULL);
				}

				// In the case there are no monitor items, adding the stop event will keep the
				// service running until a Service Stop Event occurs.
				handles[handleCount - 1] = g_serviceStopEvent;

				// now running
				setServiceStatus(SERVICE_RUNNING, false, NO_ERROR, 0);

				// wait for all threads to end and Service Stop Event
				WaitForMultipleObjects(handleCount, handles, true, INFINITE);

				// clean up
				for (size_t i = 0; i < handleCount; i++)
				{
					CloseHandle(handles[i]);
				}
				monitor::NvmMonitorBase::deleteMonitors(monitors);

				setServiceStatus(SERVICE_STOPPED, FALSE, NO_ERROR, 0);
			}
			else
			{
				logStartError("Failed to set working directory.");
				setServiceStatus(SERVICE_STOPPED, FALSE, NO_ERROR, 0);
			}

		}
		else
		{
			logStartError("CreateEvent Failed");
			setServiceStatus(SERVICE_STOPPED, FALSE, NO_ERROR, 0);
		}


	}
}