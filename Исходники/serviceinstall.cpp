/**
 * Installs or upgrades the SVC_NAME service.
 * If an existing service is already installed, we replace it with the
 * currently running process.
 *
 * @param  action The action to perform.
 * @return TRUE if the service was installed/upgraded
 */
BOOL
SvcInstall(SvcInstallAction action)
{
  // Get a handle to the local computer SCM database with full access rights.
  nsAutoServiceHandle schSCManager(OpenSCManager(NULL, NULL, 
                                                 SC_MANAGER_ALL_ACCESS));
  if (!schSCManager) {
    LOG(("Could not open service manager.  (%d)\n", GetLastError()));
    return FALSE;
  }

  WCHAR newServiceBinaryPath[MAX_PATH + 1];
  if (!GetModuleFileNameW(NULL, newServiceBinaryPath, 
                          sizeof(newServiceBinaryPath) / 
                          sizeof(newServiceBinaryPath[0]))) {
    LOG(("Could not obtain module filename when attempting to "
         "install service. (%d)\n",
         GetLastError()));
    return FALSE;
  }

  // Check if we already have the service installed.
  nsAutoServiceHandle schService(OpenServiceW(schSCManager, 
                                              SVC_NAME, 
                                              SERVICE_ALL_ACCESS));
  DWORD lastError = GetLastError();
  if (!schService && ERROR_SERVICE_DOES_NOT_EXIST != lastError) {
    // The service exists but we couldn't open it
    LOG(("Could not open service.  (%d)\n", GetLastError()));
    return FALSE;
  }
  
  if (schService) {
    // The service exists but it may not have the correct permissions.
    // This could happen if the permissions were not set correctly originally
    // or have been changed after the installation.  This will reset the 
    // permissions back to allow limited user accounts.
    if (!SetUserAccessServiceDACL(schService)) {
      LOG(("Could not reset security ACE on service handle. It might not be "
           "possible to start the service. This error should never "
           "happen.  (%d)\n", GetLastError()));
    }

    // The service exists and we opened it
    DWORD bytesNeeded;
    if (!QueryServiceConfigW(schService, NULL, 0, &bytesNeeded) && 
        GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
      LOG(("Could not determine buffer size for query service config.  (%d)\n", 
           GetLastError()));
      return FALSE;
    }

    // Get the service config information, in particular we want the binary 
    // path of the service.
    nsAutoArrayPtr<char> serviceConfigBuffer = new char[bytesNeeded];
    if (!QueryServiceConfigW(schService, 
        reinterpret_cast<QUERY_SERVICE_CONFIGW*>(serviceConfigBuffer.get()), 
        bytesNeeded, &bytesNeeded)) {
      LOG(("Could open service but could not query service config.  (%d)\n", 
           GetLastError()));
      return FALSE;
    }
    QUERY_SERVICE_CONFIGW &serviceConfig = 
      *reinterpret_cast<QUERY_SERVICE_CONFIGW*>(serviceConfigBuffer.get());

    // Check if we need to fix the service path
    BOOL servicePathWasWrong;
    static BOOL alreadyCheckedFixServicePath = FALSE;
    if (!alreadyCheckedFixServicePath) {
      if (!FixServicePath(schService, serviceConfig.lpBinaryPathName,
                          servicePathWasWrong)) {
        LOG(("Could not fix service path. This should never happen. (%d)\n",
              GetLastError()));
        // True is returned because the service is pointing to
        // maintenanceservice_tmp.exe so it actually was upgraded to the
        // newest installed service.
        return TRUE;
      } else if (servicePathWasWrong) {
        // Now that the path is fixed we should re-attempt the install.
        // This current process' image path is maintenanceservice_tmp.exe.
        // The service used to point to maintenanceservice_tmp.exe.
        // The service was just fixed to point to maintenanceservice.exe.
        // Re-attempting an install from scratch will work as normal.
        alreadyCheckedFixServicePath = TRUE;
        LOG(("Restarting install action: %d\n", action));
        return SvcInstall(action);
      }
    }

    // Ensure the service path is not quoted. We own this memory and know it to
    // be large enough for the quoted path, so it is large enough for the
    // unquoted path.  This function cannot fail.
    PathUnquoteSpacesW(serviceConfig.lpBinaryPathName);

    // Obtain the existing maintenanceservice file's version number and
    // the new file's version number.  Versions are in the format of
    // A.B.C.D.
    DWORD existingA, existingB, existingC, existingD;
    DWORD newA, newB, newC, newD; 
    BOOL obtainedExistingVersionInfo = 
      GetVersionNumberFromPath(serviceConfig.lpBinaryPathName, 
                               existingA, existingB, 
                               existingC, existingD);
    if (!GetVersionNumberFromPath(newServiceBinaryPath, newA, 
                                 newB, newC, newD)) {
      LOG(("Could not obtain version number from new path\n"));
      return FALSE;
    }

    // Check if we need to replace the old binary with the new one
    // If we couldn't get the old version info then we assume we should 
    // replace it.
    if (ForceInstallSvc == action ||
        !obtainedExistingVersionInfo || 
        (existingA < newA) ||
        (existingA == newA && existingB < newB) ||
        (existingA == newA && existingB == newB && 
         existingC < newC) ||
        (existingA == newA && existingB == newB && 
         existingC == newC && existingD < newD)) {

      // We have a newer updater, so update the description from the INI file.
      UpdateServiceDescription(schService);

      schService.reset();
      if (!StopService()) {
        return FALSE;
      }

      if (!wcscmp(newServiceBinaryPath, serviceConfig.lpBinaryPathName)) {
        LOG(("File is already in the correct location, no action needed for "
             "upgrade.  The path is: \"%ls\"\n", newServiceBinaryPath));
        return TRUE;
      }

      BOOL result = TRUE;

      // Attempt to copy the new binary over top the existing binary.
      // If there is an error we try to move it out of the way and then
      // copy it in.  First try the safest / easiest way to overwrite the file.
      if (!CopyFileW(newServiceBinaryPath, 
                     serviceConfig.lpBinaryPathName, FALSE)) {
        LOG(("Could not overwrite old service binary file. "
             "This should never happen, but if it does the next upgrade will "
             "fix it, the service is not a critical component that needs to be "
             "installed for upgrades to work. (%d)\n", GetLastError()));

        // We rename the last 3 filename chars in an unsafe way.  Manually
        // verify there are more than 3 chars for safe failure in MoveFileExW.
        const size_t len = wcslen(serviceConfig.lpBinaryPathName);
        if (len > 3) {
          // Calculate the temp file path that we're moving the file to. This 
          // is the same as the proper service path but with a .old extension.
          LPWSTR oldServiceBinaryTempPath = 
            new WCHAR[len + 1];
          memset(oldServiceBinaryTempPath, 0, (len + 1) * sizeof (WCHAR));
          wcsncpy(oldServiceBinaryTempPath, serviceConfig.lpBinaryPathName, len);
          // Rename the last 3 chars to 'old'
          wcsncpy(oldServiceBinaryTempPath + len - 3, L"old", 3);

          // Move the current (old) service file to the temp path.
          if (MoveFileExW(serviceConfig.lpBinaryPathName, 
                          oldServiceBinaryTempPath, 
                          MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
            // The old binary is moved out of the way, copy in the new one.
            if (!CopyFileW(newServiceBinaryPath, 
                           serviceConfig.lpBinaryPathName, FALSE)) {
              // It is best to leave the old service binary in this condition.
              LOG(("ERROR: The new service binary could not be copied in."
                   " The service will not be upgraded.\n"));
              result = FALSE;
            } else {
              LOG(("The new service binary was copied in by first moving the"
                   " old one out of the way.\n"));
            }

            // Attempt to get rid of the old service temp path.
            if (DeleteFileW(oldServiceBinaryTempPath)) {
              LOG(("The old temp service path was deleted: %ls.\n", 
                   oldServiceBinaryTempPath));
            } else {
              // The old temp path could not be removed.  It will be removed
              // the next time the user can't copy the binary in or on uninstall.
              LOG(("WARNING: The old temp service path was not deleted.\n"));
            }
          } else {
            // It is best to leave the old service binary in this condition.
            LOG(("ERROR: Could not move old service file out of the way from:"
                 " \"%ls\" to \"%ls\". Service will not be upgraded. (%d)\n", 
                 serviceConfig.lpBinaryPathName, 
                 oldServiceBinaryTempPath, GetLastError()));
            result = FALSE;
          }
          delete[] oldServiceBinaryTempPath;
        } else {
            // It is best to leave the old service binary in this condition.
            LOG(("ERROR: Service binary path was less than 3, service will"
                 " not be updated.  This should never happen.\n"));
            result = FALSE;
        }
      } else {
        LOG(("The new service binary was copied in.\n"));
      }

      // We made a copy of ourselves to the existing location.
      // The tmp file (the process of which we are executing right now) will be
      // left over.  Attempt to delete the file on the next reboot.
      if (MoveFileExW(newServiceBinaryPath, NULL, MOVEFILE_DELAY_UNTIL_REBOOT)) {
        LOG(("Deleting the old file path on the next reboot: %ls.\n", 
             newServiceBinaryPath));
      } else {
        LOG(("Call to delete the old file path failed: %ls.\n", 
             newServiceBinaryPath));
      }
      
      return result;
    }

    // We don't need to copy ourselves to the existing location.
    // The tmp file (the process of which we are executing right now) will be
    // left over.  Attempt to delete the file on the next reboot.
    MoveFileExW(newServiceBinaryPath, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
    
    // nothing to do, we already have a newer service installed
    return TRUE; 
  }
  
  // If the service does not exist and we are upgrading, don't install it.
  if (UpgradeSvc == action) {
    // The service does not exist and we are upgrading, so don't install it
    return TRUE;
  }

  // Quote the path only if it contains spaces.
  PathQuoteSpacesW(newServiceBinaryPath);
  // The service does not already exist so create the service as on demand
  schService.own(CreateServiceW(schSCManager, SVC_NAME, SVC_DISPLAY_NAME,
                                SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
                                SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
                                newServiceBinaryPath, NULL, NULL, NULL, 
                                NULL, NULL));
  if (!schService) {
    LOG(("Could not create Windows service. "
         "This error should never happen since a service install "
         "should only be called when elevated. (%d)\n", GetLastError()));
    return FALSE;
  } 

  if (!SetUserAccessServiceDACL(schService)) {
    LOG(("Could not set security ACE on service handle, the service will not "
         "be able to be started from unelevated processes. "
         "This error should never happen.  (%d)\n", 
         GetLastError()));
  }

  UpdateServiceDescription(schService);

  return TRUE;
}