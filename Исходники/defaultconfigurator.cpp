void DefaultConfigurator::configure(LoggerRepository* repository)
{
        repository->setConfigured(true);
        const LogString configuratorClassName(getConfiguratorClass());

        LogString configurationOptionStr(getConfigurationFileName());
        Pool pool;
        File configuration;
        if (configurationOptionStr.empty())
        {
            const char* names[] = { "log4cxx.xml", "log4cxx.properties", "log4j.xml", "log4j.properties", 0 };
            for (int i = 0; names[i] != 0; i++) {
                File candidate(names[i]);
                if (candidate.exists(pool)) {
                    configuration = candidate;
                    break;
                }
            }
        } else {
            configuration.setPath(configurationOptionStr);
        }

        if (configuration.exists(pool))
        {
                LogString msg(LOG4CXX_STR("Using configuration file ["));
                msg += configuration.getPath();
                msg += LOG4CXX_STR("] for automatic log4cxx configuration");
                LogLog::debug(msg);

            LoggerRepositoryPtr repo(repository);
                OptionConverter::selectAndConfigure(
                        configuration,
                        configuratorClassName,
                        repo);
        }
        else
        {
                if (configurationOptionStr.empty()) {
                    LogLog::debug(LOG4CXX_STR("Could not find default configuration file."));
                } else {
                    LogString msg(LOG4CXX_STR("Could not find configuration file: ["));
                    msg += configurationOptionStr;
                    msg += LOG4CXX_STR("].");
                    LogLog::debug(msg);
                }
        }

}