int main(int argc, char** argv)
#endif
{
  Logger::getInstance().log(INFO_LOG_NAME, "Application started. Hello, World!");
  Logger::getInstance().log(INFO_LOG_NAME, CString("Application version: ") + Version + " " + CString(BUILD_STR));
#if defined(WIN32) && defined(DEBUG)
  AllocConsole();
  FILE* stream = NULL;
  errno_t err = freopen_s(&stream, "CON", "w", stdout);
#endif


  BoxCar& game = BoxCar::getInstance();
  bool res = game.init();
  if (res) {
    Logger::getInstance().log(INFO_LOG_NAME, "Initialization successfully completed");
    game.run();
  } else {
    Logger::getInstance().log(ERROR_LOG_NAME, "Something went horribly wrong. Look above for details.");
  }

#if defined(WIN32) && defined(DEBUG)
  FreeConsole();
#endif
  Logger::getInstance().log(INFO_LOG_NAME, "Application ended. Bye!");
}