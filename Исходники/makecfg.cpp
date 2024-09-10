int main(int argc, char **argv)
{
  Fl::lock();
  std::string installDirectory = "";
  if (argc > 1)
    installDirectory = argv[argc - 1];
  else {
    std::string tmp = "";
#ifndef WIN32
    if (std::getenv("HOME") != (char *) 0) {
      tmp = std::getenv("HOME");
      tmp += "/.plus4emu";
    }
#endif
    Fl_File_Chooser *w =
        new Fl_File_Chooser(tmp.c_str(), "*",
                            Fl_File_Chooser::DIRECTORY
                            | Fl_File_Chooser::CREATE,
                            "Select installation directory "
                            "for plus4emu data files");
    w->show();
    w->value(tmp.c_str());
    do {
      Fl::wait(0.05);
    } while (w->shown());
    if (w->value() != (char *) 0)
      installDirectory = w->value();
    delete w;
  }
  Plus4Emu::stripString(installDirectory);
  if (installDirectory.length() == 0)
    return -1;
#ifndef WIN32
  while (installDirectory[installDirectory.length() - 1] == '/' &&
         installDirectory.length() > 1) {
    installDirectory.resize(installDirectory.length() - 1);
  }
  {
    mkdir(installDirectory.c_str(), 0755);
    std::string tmp = installDirectory;
    if (tmp[tmp.length() - 1] != '/')
      tmp += '/';
    std::string tmp2 = tmp + "config";
    mkdir(tmp2.c_str(), 0755);
    tmp2 = tmp + "demo";
    mkdir(tmp2.c_str(), 0755);
    tmp2 = tmp + "disk";
    mkdir(tmp2.c_str(), 0755);
    tmp2 = tmp + "progs";
    mkdir(tmp2.c_str(), 0755);
    tmp2 = tmp + "roms";
    mkdir(tmp2.c_str(), 0755);
    tmp2 = tmp + "tape";
    mkdir(tmp2.c_str(), 0755);
  }
#else
  while ((installDirectory[installDirectory.length() - 1] == '/' ||
          installDirectory[installDirectory.length() - 1] == '\\') &&
         !(installDirectory.length() <= 1 ||
           (installDirectory.length() == 3 && installDirectory[1] == ':'))) {
    installDirectory.resize(installDirectory.length() - 1);
  }
  {
    _mkdir(installDirectory.c_str());
    std::string tmp = installDirectory;
    if (tmp[tmp.length() - 1] != '/' && tmp[tmp.length() - 1] != '\\')
      tmp += '\\';
    std::string tmp2 = tmp + "config";
    _mkdir(tmp2.c_str());
    tmp2 = tmp + "demo";
    _mkdir(tmp2.c_str());
    tmp2 = tmp + "disk";
    _mkdir(tmp2.c_str());
    tmp2 = tmp + "progs";
    _mkdir(tmp2.c_str());
    tmp2 = tmp + "roms";
    _mkdir(tmp2.c_str());
    tmp2 = tmp + "tape";
    _mkdir(tmp2.c_str());
  }
#endif
#ifdef WIN32
  uint8_t c = '\\';
#else
  uint8_t c = '/';
#endif
  if (installDirectory[installDirectory.length() - 1] != c)
    installDirectory += c;
  std::string configDirectory = installDirectory + "config";
  configDirectory += c;
  std::string romDirectory = installDirectory + "roms";
  romDirectory += c;
  Plus4EmuConfigInstallerGUI  *gui = new Plus4EmuConfigInstallerGUI();
  gui->mainWindow->show();
  do {
    Fl::wait(0.05);
  } while (gui->mainWindow->shown());
  try {
    Plus4Emu::ConfigurationDB     *config = (Plus4Emu::ConfigurationDB *) 0;
    Plus4EmuMachineConfiguration  *mCfg = (Plus4EmuMachineConfiguration *) 0;
    if (gui->enableCfgInstall) {
      Plus4EmuDisplaySndConfiguration   *dsCfg =
          (Plus4EmuDisplaySndConfiguration *) 0;
      config = new Plus4Emu::ConfigurationDB();
      {
        Plus4EmuGUIConfiguration  *gCfg =
            new Plus4EmuGUIConfiguration(*config, installDirectory);
        try {
          Plus4Emu::File  f;
          config->saveState(f);
          f.writeFile("gui_cfg.dat", true);
        }
        catch (std::exception& e) {
          gui->errorMessage(e.what());
        }
        delete gCfg;
      }
      delete config;
      config = new Plus4Emu::ConfigurationDB();
      mCfg = new Plus4EmuMachineConfiguration(*config, 6, romDirectory);
      dsCfg = new Plus4EmuDisplaySndConfiguration(*config);
      setKeyboardConfiguration(*config, (gui->keyboardMapHU ? 5 : 4));
      try {
        Plus4Emu::File  f;
        config->saveState(f);
        f.writeFile("plus4cfg.dat", true);
      }
      catch (std::exception& e) {
        gui->errorMessage(e.what());
      }
      delete config;
      delete mCfg;
      delete dsCfg;
      config = (Plus4Emu::ConfigurationDB *) 0;
      mCfg = (Plus4EmuMachineConfiguration *) 0;
    }
    for (int i = 0; i < 16; i++) {
      config = new Plus4Emu::ConfigurationDB();
      mCfg = new Plus4EmuMachineConfiguration(*config, i, romDirectory);
      try {
        std::string fileName = configDirectory;
        fileName += machineConfigFileNames[i];
        config->saveState(fileName.c_str(), false);
      }
      catch (std::exception& e) {
        gui->errorMessage(e.what());
      }
      delete config;
      delete mCfg;
      config = (Plus4Emu::ConfigurationDB *) 0;
      mCfg = (Plus4EmuMachineConfiguration *) 0;
    }
    for (int i = 0; i < 8; i++) {
      if (keyboardConfigFileNames[i] != (char *) 0) {
        config = new Plus4Emu::ConfigurationDB();
        try {
          setKeyboardConfiguration(*config, i);
          std::string fileName = configDirectory;
          fileName += keyboardConfigFileNames[i];
          config->saveState(fileName.c_str(), false);
        }
        catch (std::exception& e) {
          gui->errorMessage(e.what());
        }
        delete config;
        config = (Plus4Emu::ConfigurationDB *) 0;
      }
    }
  }
  catch (std::exception& e) {
    gui->errorMessage(e.what());
    delete gui;
    return -1;
  }
  delete gui;
  return 0;
}