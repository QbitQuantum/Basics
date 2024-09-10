void ResourceFinder::includeHomeDir(const char* filename)
{
#ifdef _WIN32

  // %AppData%/Aseprite/filename
  wchar_t* env = _wgetenv(L"AppData");
  if (env) {
    std::string path = base::join_path(base::to_utf8(env), "Aseprite");
    path = base::join_path(path, filename);
    addPath(path);
    m_default = path;
  }

#else

  char* env = std::getenv("HOME");
  char buf[4096];

  if ((env) && (*env)) {
    // $HOME/filename
    sprintf(buf, "%s/%s", env, filename);
    addPath(buf);
  }
  else {
    LOG("You don't have set $HOME variable\n");
    addPath(filename);
  }

#endif
}