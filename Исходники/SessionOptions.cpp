core::ProgramStatus Options::read(int argc, char * const argv[])
{
   using namespace boost::program_options ;
   
   // get the shared secret
   monitorSharedSecret_ = core::system::getenv(kMonitorSharedSecretEnvVar);
   core::system::unsetenv(kMonitorSharedSecretEnvVar);

   // compute the resource path
   FilePath resourcePath;
   Error error = core::system::installPath("..", argv[0], &resourcePath);
   if (error)
   {
      LOG_ERROR_MESSAGE("Unable to determine install path: "+error.summary());
      return ProgramStatus::exitFailure();
   }

   // detect running in OSX bundle and tweak resource path
#ifdef __APPLE__
   if (resourcePath.complete("Info.plist").exists())
      resourcePath = resourcePath.complete("Resources");
#endif

   // detect running in x64 directory and tweak resource path
#ifdef _WIN32
   if (resourcePath.complete("x64").exists())
      resourcePath = resourcePath.parent();
#endif

   // verify installation flag
   options_description verify("verify");
   verify.add_options()
     (kVerifyInstallationSessionOption,
     value<bool>(&verifyInstallation_)->default_value(false),
     "verify the current installation");

   // program - name and execution
   options_description program("program");
   program.add_options()
      (kProgramModeSessionOption,
         value<std::string>(&programMode_)->default_value("server"),
         "program mode (desktop or server");
   
   // log -- logging options
   options_description log("log");
   log.add_options()
      ("log-stderr",
      value<bool>(&logStderr_)->default_value(true),
      "write log entries to stderr");

   // agreement
   options_description agreement("agreement");
   agreement.add_options()
      ("agreement-file",
      value<std::string>(&agreementFilePath_)->default_value(""),
      "agreement file");

   // docs url
   options_description docs("docs");
   docs.add_options()
      ("docs-url",
       value<std::string>(&docsURL_)->default_value(""),
       "custom docs url");

   // www options
   options_description www("www") ;
   www.add_options()
      ("www-local-path",
         value<std::string>(&wwwLocalPath_)->default_value("www"),
         "www local path")
      ("www-symbol-maps-path",
         value<std::string>(&wwwSymbolMapsPath_)->default_value(
                                                         "www-symbolmaps"),
         "www symbol maps path")
      ("www-port",
         value<std::string>(&wwwPort_)->default_value("8787"),
         "port to listen on")
      ("www-address",
         value<std::string>(&wwwAddress_)->default_value("127.0.0.1"),
         "port to listen on")
      ("standalone",
         value<bool>(&standalone_)->default_value(false),
         "run standalone");

   // session options
   std::string saveActionDefault;
   options_description session("session") ;
   session.add_options()
      (kTimeoutSessionOption,
         value<int>(&timeoutMinutes_)->default_value(120),
         "session timeout (minutes)" )
      (kDisconnectedTimeoutSessionOption,
         value<int>(&disconnectedTimeoutMinutes_)->default_value(0),
         "session disconnected timeout (minutes)" )
      ("session-preflight-script",
         value<std::string>(&preflightScript_)->default_value(""),
         "session preflight script")
      ("session-create-public-folder",
         value<bool>(&createPublicFolder_)->default_value(false),
         "automatically create public folder")
      ("session-create-profile",
         value<bool>(&createProfile_)->default_value(false),
         "automatically create .Rprofile")
      ("session-rprofile-on-resume-default",
          value<bool>(&rProfileOnResumeDefault_)->default_value(false),
          "default user setting for running Rprofile on resume")
      ("session-save-action-default",
       value<std::string>(&saveActionDefault)->default_value(""),
          "default save action (yes, no, or ask)");

   // allow options
   options_description allow("allow");
   allow.add_options()
      ("allow-vcs-executable-edit",
         value<bool>(&allowVcsExecutableEdit_)->default_value(true),
         "allow editing of vcs executables")
      ("allow-r-cran-repos-edit",
         value<bool>(&allowCRANReposEdit_)->default_value(true),
         "Allow editing of CRAN repository")
      ("allow-vcs",
         value<bool>(&allowVcs_)->default_value(true),
         "allow use of version control features")
      ("allow-package-installation",
         value<bool>(&allowPackageInstallation_)->default_value(true),
         "allow installation of packages from the packages pane")
      ("allow-shell",
         value<bool>(&allowShell_)->default_value(true),
         "allow access to shell dialog")
      ("allow-file-downloads",
         value<bool>(&allowFileDownloads_)->default_value(true),
         "allow file downloads from the files pane")
      ("allow-remove-public-folder",
         value<bool>(&allowRemovePublicFolder_)->default_value(true),
         "allow removal of the user public folder")
      ("allow-rpubs-publish",
         value<bool>(&allowRpubsPublish_)->default_value(true),
        "allow publishing to rpubs");

   // r options
   bool rShellEscape; // no longer works but don't want to break any
                      // config files which formerly used it
                      // TODO: eliminate this option entirely
   options_description r("r") ;
   r.add_options()
      ("r-core-source",
         value<std::string>(&coreRSourcePath_)->default_value("R"),
         "Core R source path")
      ("r-modules-source", 
         value<std::string>(&modulesRSourcePath_)->default_value("R/modules"),
         "Modules R source path")
      ("r-session-library",
         value<std::string>(&sessionLibraryPath_)->default_value("R/library"),
         "R library path")
      ("r-session-packages",
         value<std::string>(&sessionPackagesPath_)->default_value("R/packages"),
         "R packages path")
      ("r-session-package-archives",
          value<std::string>(&sessionPackageArchivesPath_)->default_value("R/packages"),
         "R package archives path")
      ("r-libs-user",
         value<std::string>(&rLibsUser_)->default_value(""),
         "R user library path")
      ("r-cran-repos",
         value<std::string>(&rCRANRepos_)->default_value(""),
         "Default CRAN repository")
      ("r-auto-reload-source",
         value<bool>(&autoReloadSource_)->default_value(false),
         "Reload R source if it changes during the session")
      ("r-compatible-graphics-engine-version",
         value<int>(&rCompatibleGraphicsEngineVersion_)->default_value(10),
         "Maximum graphics engine version we are compatible with")
      ("r-resources-path",
         value<std::string>(&rResourcesPath_)->default_value("resources"),
         "Directory containing external resources")
      ("r-shell-escape",
         value<bool>(&rShellEscape)->default_value(false),
         "Support shell escape (deprecated, no longer works)")
      ("r-home-dir-override",
         value<std::string>(&rHomeDirOverride_)->default_value(""),
         "Override for R_HOME (used for debug configurations)")
      ("r-doc-dir-override",
         value<std::string>(&rDocDirOverride_)->default_value(""),
         "Override for R_DOC_DIR (used for debug configurations)");

   // limits options
   options_description limits("limits");
   limits.add_options()
      ("limit-file-upload-size-mb",
       value<int>(&limitFileUploadSizeMb_)->default_value(0),
       "limit of file upload size")
      ("limit-cpu-time-minutes",
       value<int>(&limitCpuTimeMinutes_)->default_value(0),
       "limit on time of top level computations")
      ("limit-xfs-disk-quota",
       value<bool>(&limitXfsDiskQuota_)->default_value(false),
       "limit xfs disk quota");
   
   // external options
   options_description external("external");
   external.add_options()
      ("external-rpostback-path", 
       value<std::string>(&rpostbackPath_)->default_value(kDefaultPostbackPath),
       "Path to rpostback executable")
      ("external-consoleio-path",
       value<std::string>(&consoleIoPath_)->default_value("bin/consoleio.exe"),
       "Path to consoleio executable")
      ("external-gnudiff-path",
       value<std::string>(&gnudiffPath_)->default_value("bin/gnudiff"),
       "Path to gnudiff utilities (windows-only)")
      ("external-gnugrep-path",
       value<std::string>(&gnugrepPath_)->default_value("bin/gnugrep"),
       "Path to gnugrep utilities (windows-only)")
      ("external-msysssh-path",
       value<std::string>(&msysSshPath_)->default_value("bin/msys_ssh"),
       "Path to msys_ssh utilities (windows-only)")
      ("external-sumatra-path",
       value<std::string>(&sumatraPath_)->default_value("bin/sumatra"),
       "Path to SumatraPDF (windows-only)")
      ("external-hunspell-dictionaries-path",
       value<std::string>(&hunspellDictionariesPath_)->default_value("resources/dictionaries"),
       "Path to hunspell dictionaries")
      ("external-mathjax-path",
        value<std::string>(&mathjaxPath_)->default_value("resources/mathjax-23"),
        "Path to mathjax library")
      ("external-pandoc-path",
        value<std::string>(&pandocPath_)->default_value(kDefaultPandocPath),
        "Path to pandoc binaries");

   // user options (default user identity to current username)
   std::string currentUsername = core::system::username();
   options_description user("user") ;
   user.add_options()
      (kUserIdentitySessionOption "," kUserIdentitySessionOptionShort,
       value<std::string>(&userIdentity_)->default_value(currentUsername),
       "user identity" )
      (kShowUserIdentitySessionOption,
       value<bool>(&showUserIdentity_)->default_value(true),
       "show the user identity");

   // overlay options
   options_description overlay("overlay");
   addOverlayOptions(&overlay);

   // define program options
   FilePath defaultConfigPath("/etc/rstudio/rsession.conf");
   std::string configFile = defaultConfigPath.exists() ?
                                 defaultConfigPath.absolutePath() : "";
   core::program_options::OptionsDescription optionsDesc("rsession",
                                                         configFile);

   optionsDesc.commandLine.add(verify);
   optionsDesc.commandLine.add(program);
   optionsDesc.commandLine.add(log);
   optionsDesc.commandLine.add(agreement);
   optionsDesc.commandLine.add(docs);
   optionsDesc.commandLine.add(www);
   optionsDesc.commandLine.add(session);
   optionsDesc.commandLine.add(allow);
   optionsDesc.commandLine.add(r);
   optionsDesc.commandLine.add(limits);
   optionsDesc.commandLine.add(external);
   optionsDesc.commandLine.add(user);

   // define groups included in config-file processing
   optionsDesc.configFile.add(program);
   optionsDesc.configFile.add(log);
   optionsDesc.configFile.add(agreement);
   optionsDesc.configFile.add(docs);
   optionsDesc.configFile.add(www);
   optionsDesc.configFile.add(session);
   optionsDesc.configFile.add(allow);
   optionsDesc.configFile.add(r);
   optionsDesc.configFile.add(limits);
   optionsDesc.configFile.add(external);
   optionsDesc.configFile.add(user);
   optionsDesc.configFile.add(overlay);

   // read configuration
   ProgramStatus status = core::program_options::read(optionsDesc, argc,argv);
   if (status.exit())
      return status;
   
   // make sure the program mode is valid
   if (programMode_ != kSessionProgramModeDesktop &&
       programMode_ != kSessionProgramModeServer)
   {
      LOG_ERROR_MESSAGE("invalid program mode: " + programMode_);
      return ProgramStatus::exitFailure();
   }

   // call overlay hooks
   resolveOverlayOptions();
   std::string errMsg;
   if (!validateOverlayOptions(&errMsg))
   {
      program_options::reportError(errMsg, ERROR_LOCATION);
      return ProgramStatus::exitFailure();
   }

   // compute program identity
   programIdentity_ = "rsession-" + userIdentity_;

   // provide special home path in temp directory if we are verifying
   if (verifyInstallation_)
   {
      // we create a special home directory in server mode (since the
      // user we are running under might not have a home directory)
      if (programMode_ == kSessionProgramModeServer)
      {
         verifyInstallationHomeDir_ = "/tmp/rstudio-verify-installation";
         Error error = FilePath(verifyInstallationHomeDir_).ensureDirectory();
         if (error)
         {
            LOG_ERROR(error);
            return ProgramStatus::exitFailure();
         }
         core::system::setenv("R_USER", verifyInstallationHomeDir_);
      }
   }

   // compute user paths
   r_util::SessionType sessionType =
      (programMode_ == kSessionProgramModeDesktop) ?
                                    r_util::SessionTypeDesktop :
                                    r_util::SessionTypeServer;

   r_util::UserDirectories userDirs = r_util::userDirectories(sessionType);
   userHomePath_ = userDirs.homePath;
   userScratchPath_ = userDirs.scratchPath;

   // set HOME if we are in standalone mode (this enables us to reflect
   // R_USER back into HOME on Linux)
   if (standalone())
      core::system::setenv("HOME", userHomePath_);

   // session timeout seconds is always -1 in desktop mode
   if (programMode_ == kSessionProgramModeDesktop)
      timeoutMinutes_ = 0;

   // convert string save action default to intenger
   if (saveActionDefault == "yes")
      saveActionDefault_ = r::session::kSaveActionSave;
   else if (saveActionDefault == "no")
      saveActionDefault_ = r::session::kSaveActionNoSave;
   else if (saveActionDefault == "ask" || saveActionDefault.empty())
      saveActionDefault_ = r::session::kSaveActionAsk;
   else
   {
      program_options::reportWarnings(
         "Invalid value '" + saveActionDefault + "' for "
         "session-save-action-default. Valid values are yes, no, and ask.",
         ERROR_LOCATION);
      saveActionDefault_ = r::session::kSaveActionAsk;
   }

   // convert relative paths by completing from the app resource path
   resolvePath(resourcePath, &rResourcesPath_);
   resolvePath(resourcePath, &agreementFilePath_);
   resolvePath(resourcePath, &wwwLocalPath_);
   resolvePath(resourcePath, &wwwSymbolMapsPath_);
   resolvePath(resourcePath, &coreRSourcePath_);
   resolvePath(resourcePath, &modulesRSourcePath_);
   resolvePath(resourcePath, &sessionLibraryPath_);
   resolvePath(resourcePath, &sessionPackagesPath_);
   resolvePath(resourcePath, &sessionPackageArchivesPath_);
   resolvePostbackPath(resourcePath, &rpostbackPath_);
#ifdef _WIN32
   resolvePath(resourcePath, &consoleIoPath_);
   resolvePath(resourcePath, &gnudiffPath_);
   resolvePath(resourcePath, &gnugrepPath_);
   resolvePath(resourcePath, &msysSshPath_);
   resolvePath(resourcePath, &sumatraPath_);
#endif
   resolvePath(resourcePath, &hunspellDictionariesPath_);
   resolvePath(resourcePath, &mathjaxPath_);
   resolvePandocPath(resourcePath, &pandocPath_);

   // shared secret with parent
   secret_ = core::system::getenv("RS_SHARED_SECRET");
   /* SECURITY: Need RS_SHARED_SECRET to be available to
      rpostback. However, we really ought to communicate
      it in a more secure manner than this, at least on
      Windows where even within the same user session some
      processes can have different priviliges (integrity
      levels) than others. For example, using a named pipe
      with proper SACL to retrieve the shared secret, where
      the name of the pipe is in an environment variable. */
   //core::system::unsetenv("RS_SHARED_SECRET");

   // initial working dir override
   initialWorkingDirOverride_ = core::system::getenv(kRStudioInitialWorkingDir);
   core::system::unsetenv(kRStudioInitialWorkingDir);

   // initial environment file override
   initialEnvironmentFileOverride_ = core::system::getenv(kRStudioInitialEnvironment);
   core::system::unsetenv(kRStudioInitialEnvironment);

   // initial project
   initialProjectPath_ = core::system::getenv(kRStudioInitialProject);
   core::system::unsetenv(kRStudioInitialProject);

   // limit rpc client uid
   limitRpcClientUid_ = -1;
   std::string limitUid = core::system::getenv(kRStudioLimitRpcClientUid);
   if (!limitUid.empty())
   {
      limitRpcClientUid_ = core::safe_convert::stringTo<int>(limitUid, -1);
      core::system::unsetenv(kRStudioLimitRpcClientUid);
   }

   // return status
   return status;
}