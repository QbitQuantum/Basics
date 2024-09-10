static void setup_python(int argc, char **argv) {
  char *pathlist = NULL;
  TCHAR szPath[MAX_PATH];
  std::string module_path;
  if (GetModuleFileName(NULL, szPath, MAX_PATH)) {
    CHAR char_path[MAX_PATH] = {0};
    WideCharToMultiByte(CP_UTF8, 0, szPath, -1, char_path, MAX_PATH, NULL, NULL);
    std::string full_path(char_path);
    size_t path_end = full_path.find_last_of('\\');
    if (path_end != std::string::npos)
      module_path = full_path.substr(0, path_end + 1);
  }

#if 0
  if (_dupenv_s(&pathlist, &bufsize, "PYTHONPATH") == 0 && pathlist)
  {
    int len = strlen("PYTHONPATH")+1+strlen(pathlist)+strlen(";python;scripts")+1;
    char *tmp = (char*)malloc(len);
    sprintf_s(tmp, len, "PYTHONPATH=%s;python;scripts", pathlist);
    _putenv(tmp);
    free(tmp);
  }
  else
#endif

  SetDllDirectoryA((module_path + "..").c_str());

  // This should initialize PYTHONPATH, but for some reason it doesn't work when built in VS2010.
  std::string pythonpath;
  pythonpath.append(module_path).append("modules;");
  pythonpath.append(module_path).append("python;");
  pythonpath.append(module_path).append("python\\Lib;");
  pythonpath.append(module_path).append("python\\libs;");
  pythonpath.append(module_path).append("python\\DLLs;");
  _putenv_s("PYTHONHOME", "python");
  _putenv_s("PYTHONPATH", pythonpath.c_str());
  if (pathlist)
    free(pathlist);

  Py_SetProgramName(argv[0]);

  // Here comes some ugly hack to fix PYTHONPATH init problem.
  // Create dummy site package to avoid error import site message from Py_Initialize();
  FILE *pFile;
  pFile = fopen("site.py", "w");
  if (pFile != NULL)
    fclose(pFile);

  Py_Initialize();

  // Delete dummy site module.
  remove("site.py");
  remove("site.pyc");

  PySys_SetArgv(argc, argv);

  // Now import sys and modify PYTHONPATH.
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('modules')");
  PyRun_SimpleString("sys.path.append('python')");
  PyRun_SimpleString("sys.path.append('python\\Lib')");
  PyRun_SimpleString("sys.path.append('python\\libs')");
  PyRun_SimpleString("sys.path.append('python\\DLLs')");

  // Reload site module with real module from updated PYTHONPATH.
  PyRun_SimpleString("import site");
  PyRun_SimpleString("reload(site)");
}