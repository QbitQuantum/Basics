// ----------------------------------------------------
// Function called when we want to stop the server.
// This code is called by the stop-ds.bat batch file to stop the server
// in windows.
// This function expects just one parameter to be passed
// to the executable: the directory of the server we want
// to stop.
//
// If the instance could be stopped the pid file
// is removed.  This is done for security reasons: if we do
// not delete the pid file and the old pid of the process
// is used by a new process, when we call again this executable
// the new process will be killed.
// Note: even if the code in the class org.opends.server.core.DirectoryServer
// sets the pid file to be deleted on the exit of the process
// the file is not always deleted.
//
// Returns 0 if the instance could be stopped using the
// pid stored in a file of the server installation and
// -1 otherwise.
// ----------------------------------------------------
int stop(const char* instanceDir)
{
  int returnCode = -1;

  int childPid;

  debug("Attempting to stop the server running at root '%s'.", instanceDir);

  childPid = getPid(instanceDir);

  if (childPid != 0)
  {
    if (killProcess(childPid))
    {
      returnCode = 0;
      deletePidFile(instanceDir);
    }
  }
  else
  {
    debug("Could not stop the server running at root '%s' because the pid could not be located.", instanceDir);
  }

  return returnCode;
} // stop