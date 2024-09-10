int main (int argc, char** argv)
{
  RTC::Manager* manager;
  manager = RTC::Manager::init(argc, argv);

  // Initialize manager
  manager->init(argc, argv);

#ifdef _WINDOWS

  std::string path = getParam("manager.modules.load_path");
  coil::eraseBlank(path);

  coil::vstring pathList = coil::split(path, ",");

  for (int i = 0; i < pathList.size(); i++)
  {
	  std::string filepath = pathList[i];

	  char szFullPath[MAX_PATH];
	  _fullpath(szFullPath, filepath.c_str(), sizeof(szFullPath) / sizeof(szFullPath[0]));
	  std::string path = "PATH=";
	  path += getenv("PATH");
	  path += ";";
	  path += szFullPath;
	  putenv(path.c_str());

  }
#endif

  // Set module initialization proceduer
  // This procedure will be invoked in activateManager() function.
  manager->setModuleInitProc(MyModuleInit);

  // Activate manager and register to naming service
  manager->activateManager();

  // run the manager in blocking mode
  // runManager(false) is the default.
  manager->runManager();

  // If you want to run the manager in non-blocking mode, do like this
  // manager->runManager(true);

  return 0;
}