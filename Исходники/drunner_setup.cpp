   cResult check_setup()
   {
      const params & p(*GlobalContext::getParams().get());

      // check prereqs (e.g. docker installed).
      _check_prerequisits();

      // -----------------------------------------------------------------------------
      // create directory structure.
      _makedirectory(drunnerPaths::getPath_Root(), S_700);
      _makedirectory(drunnerPaths::getPath_Bin(), S_700);
      _makedirectory(drunnerPaths::getPath_dServices(), S_700);
      _makedirectory(drunnerPaths::getPath_Temp(), S_700);
      _makedirectory(drunnerPaths::getPath_HostVolumes(), S_700);
      _makedirectory(drunnerPaths::getPath_Settings(), S_700);
      _makedirectory(drunnerPaths::getPath_Logs(), S_700);
      _makedirectory(drunnerPaths::getPath_GitCache(), S_700);

      // On windows, we copy the executable to the .drunner/bin folder and make the .drunner folder hidden.
      // On Linux drunner is manually copied to /usr/local/bin (or wherever) by the user as part of the install process.
#ifdef _WIN32
      _copyexe();
      // make root hidden on windows.
      drunner_assert(0 != SetFileAttributesA(drunnerPaths::getPath_Root().toString().c_str(), FILE_ATTRIBUTE_HIDDEN), "Couldn't change attributes on the .drunner directory");
#endif

      // -----------------------------------------------------------------------------
      // generate plugin scripts
      GlobalContext::getPlugins()->generate_plugin_scripts();

      // -----------------------------------------------------------------------------
      // get latest root util and proxy images.
      utils_docker::pullImage(drunnerPaths::getdrunnerUtilsImage());
      utils_docker::pullImage(drunnerPaths::getdrunnerProxyImage());

      // write settings.
      GlobalContext::getSettings()->savevariables();

      // Create proxy docker network
      utils_docker::createDockerNetwork(proxy::networkName());

      // -----------------------------------------------------------------------------
      // Finished!
      return kRSuccess;
   }