int main(int argc, char **argv)
{
  Aria::init();
  ArArgumentParser argParser(&argc, argv);
  argParser.loadDefaultArguments();
  if (argc < 2 || !Aria::parseArgs() || argParser.checkArgument("-help"))
  {
    ArLog::log(ArLog::Terse, "configExample usage: configExample <config file>.\nFor example, \"configExample examples/configExample.cfg\".");
    Aria::logOptions();
    Aria::shutdown();
    return 1;
  }
  
  // Object containing config parameters, and responding to changes:
  ConfigExample configExample;

  // Load a config file given on the command line into the global 
  // ArConfig object kept by Aria.  Normally ArConfig expects config
  // files to be in the main ARIA directory (i.e. /usr/local/Aria or
  // a directory specified by the $ARIA environment variable).
  char error[512];
  const char* filename = argParser.getArg(1);
  ArConfig* config = Aria::getConfig();
  ArLog::log(ArLog::Normal, "configExample: loading configuration file \"%s\"...", filename);
  if (! config->parseFile(filename, true, false, error, 512) )
  {
    ArLog::log(ArLog::Terse, "configExample: Error loading configuration file \"%s\" %s. Try \"examples/configExample.cfg\".", filename, error);
    Aria::shutdown();
    return -1;
  }

  ArLog::log(ArLog::Normal, "configExample: Loaded configuration file \"%s\".", filename);
  
  // After changing a config value, you should invoke the callbacks:
  ArConfigSection* section = config->findSection("Example Section");
  if (section)
  {
    ArConfigArg* arg = section->findParam("ExampleBoolParameter");
    if (arg)
    {
      arg->setBool(!arg->getBool());
      if (! config->callProcessFileCallBacks(false, error, 512) )
      {
        ArLog::log(ArLog::Terse, "configExample: Error processing modified config: %s.", error);
      }
      else
      {
        ArLog::log(ArLog::Normal, "configExample: Successfully modified config and invoked callbacks.");
      }
    }
  }

  // You can save the configuration as well:
  ArLog::log(ArLog::Normal, "configExample: Saving configuration...");
  if(!config->writeFile(filename))
  {
    ArLog::log(ArLog::Terse, "configExample: Error saving configuration to file \"%s\"!", filename);
  }

  // end of program.
  ArLog::log(ArLog::Normal, "configExample: end of program.");
  Aria::shutdown();
  return 0;
}