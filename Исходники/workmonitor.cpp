/**
 * Runs an update process as the service using the SYSTEM account.
 *
 * @param  argc           The number of arguments in argv
 * @param  argv           The arguments normally passed to updater.exe
 *                        argv[0] must be the path to updater.exe
 * @param  processStarted Set to TRUE if the process was started.
 * @return TRUE if the update process was run had a return code of 0.
 */
BOOL
StartUpdateProcess(int argc,
                   LPWSTR *argv,
                   LPCWSTR installDir,
                   BOOL &processStarted)
{
  LOG(("Starting update process as the service in session 0."));
  STARTUPINFO si = {0};
  si.cb = sizeof(STARTUPINFO);
  si.lpDesktop = L"winsta0\\Default";
  PROCESS_INFORMATION pi = {0};

  // The updater command line is of the form:
  // updater.exe update-dir apply [wait-pid [callback-dir callback-path args]]
  LPWSTR cmdLine = MakeCommandLine(argc, argv);

  // If we're about to start the update process from session 0,
  // then we should not show a GUI.  This only really needs to be done
  // on Vista and higher, but it's better to keep everything consistent
  // across all OS if it's of no harm.
  if (argc >= 2 ) {
    // Setting the desktop to blank will ensure no GUI is displayed
    si.lpDesktop = L"";
    si.dwFlags |= STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
  }

  // We move the updater.ini file out of the way because we will handle 
  // executing PostUpdate through the service.  We handle PostUpdate from
  // the service because there are some per user things that happen that
  // can't run in session 0 which we run updater.exe in.
  // Once we are done running updater.exe we rename updater.ini back so
  // that if there were any errors the next updater.exe will run correctly.
  WCHAR updaterINI[MAX_PATH + 1];
  WCHAR updaterINITemp[MAX_PATH + 1];
  BOOL selfHandlePostUpdate = FALSE;
  // We use the updater.ini from the same directory as the updater.exe
  // because of background updates.
  if (PathGetSiblingFilePath(updaterINI, argv[0], L"updater.ini") &&
      PathGetSiblingFilePath(updaterINITemp, argv[0], L"updater.tmp")) {
    selfHandlePostUpdate = MoveFileExW(updaterINI, updaterINITemp, 
                                       MOVEFILE_REPLACE_EXISTING);
  }

  // Add an env var for MOZ_USING_SERVICE so the updater.exe can
  // do anything special that it needs to do for service updates.
  // Search in updater.cpp for more info on MOZ_USING_SERVICE.
  putenv(const_cast<char*>("MOZ_USING_SERVICE=1"));
  LOG(("Starting service with cmdline: %ls", cmdLine));
  processStarted = CreateProcessW(argv[0], cmdLine, 
                                  nullptr, nullptr, FALSE, 
                                  CREATE_DEFAULT_ERROR_MODE, 
                                  nullptr, 
                                  nullptr, &si, &pi);
  // Empty value on putenv is how you remove an env variable in Windows
  putenv(const_cast<char*>("MOZ_USING_SERVICE="));
  
  BOOL updateWasSuccessful = FALSE;
  if (processStarted) {
    // Wait for the updater process to finish
    LOG(("Process was started... waiting on result."));
    DWORD waitRes = WaitForSingleObject(pi.hProcess, TIME_TO_WAIT_ON_UPDATER);
    if (WAIT_TIMEOUT == waitRes) {
      // We waited a long period of time for updater.exe and it never finished
      // so kill it.
      TerminateProcess(pi.hProcess, 1);
    } else {
      // Check the return code of updater.exe to make sure we get 0
      DWORD returnCode;
      if (GetExitCodeProcess(pi.hProcess, &returnCode)) {
        LOG(("Process finished with return code %d.", returnCode));
        // updater returns 0 if successful.
        updateWasSuccessful = (returnCode == 0);
      } else {
        LOG_WARN(("Process finished but could not obtain return code."));
      }
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Check just in case updater.exe didn't change the status from
    // applying.  If this is the case we report an error.
    BOOL isApplying = FALSE;
    if (IsStatusApplying(argv[1], isApplying) && isApplying) {
      if (updateWasSuccessful) {
        LOG(("update.status is still applying even know update "
             " was successful."));
        if (!WriteStatusFailure(argv[1], 
                                SERVICE_STILL_APPLYING_ON_SUCCESS)) {
          LOG_WARN(("Could not write update.status still applying on"
                    " success error."));
        }
        // Since we still had applying we know updater.exe didn't do its
        // job correctly.
        updateWasSuccessful = FALSE;
      } else {
        LOG_WARN(("update.status is still applying and update was not successful."));
        if (!WriteStatusFailure(argv[1], 
                                SERVICE_STILL_APPLYING_ON_FAILURE)) {
          LOG_WARN(("Could not write update.status still applying on"
                    " success error."));
        }
      }
    }
  } else {
    DWORD lastError = GetLastError();
    LOG_WARN(("Could not create process as current user, "
              "updaterPath: %ls; cmdLine: %ls.  (%d)",
              argv[0], cmdLine, lastError));
  }

  // Now that we're done with the update, restore back the updater.ini file
  // We use it ourselves, and also we want it back in case we had any type 
  // of error so that the normal update process can use it.
  if (selfHandlePostUpdate) {
    MoveFileExW(updaterINITemp, updaterINI, MOVEFILE_REPLACE_EXISTING);

    // Only run the PostUpdate if the update was successful
    if (updateWasSuccessful && argc > 2) {
      LPCWSTR updateInfoDir = argv[1];
      bool backgroundUpdate = IsUpdateBeingStaged(argc, argv);

      // Launch the PostProcess with admin access in session 0.  This is
      // actually launching the post update process but it takes in the 
      // callback app path to figure out where to apply to.
      // The PostUpdate process with user only access will be done inside
      // the unelevated updater.exe after the update process is complete
      // from the service.  We don't know here which session to start
      // the user PostUpdate process from.
      // Note that we don't need to do this if we're just staging the
      // update in the background, as the PostUpdate step runs when
      // performing the replacing in that case.
      if (!backgroundUpdate) {
        LOG(("Launching post update process as the service in session 0."));
        if (!LaunchWinPostProcess(installDir, updateInfoDir, true, nullptr)) {
          LOG_WARN(("The post update process could not be launched."
                    " installDir: %ls, updateInfoDir: %ls",
                    installDir, updateInfoDir));
        }
      }
    }
  }

  free(cmdLine);
  return updateWasSuccessful;
}