void OptionConverter::selectAndConfigure(const File& configFileName,
         const LogString& _clazz, spi::LoggerRepositoryPtr& hierarchy)
{
        ConfiguratorPtr configurator;
        LogString clazz = _clazz;

        LogString filename(configFileName.getPath());
        if(clazz.empty() 
                && filename.length() > 4
                && StringHelper::equalsIgnoreCase(
                   filename.substr(filename.length() -4), 
                   LOG4CXX_STR(".XML"), LOG4CXX_STR(".xml")))
        {
            clazz = log4cxx::xml::DOMConfigurator::getStaticClass().toString();
        }

        if(!clazz.empty())
        {
                LogLog::debug(LOG4CXX_STR("Preferred configurator class: ") + clazz);
                configurator = instantiateByClassName(clazz,
                        Configurator::getStaticClass(),
                        0);
                if(configurator == 0)
                {
                        LogLog::error(LOG4CXX_STR("Could not instantiate configurator [")
                                 + clazz + LOG4CXX_STR("]."));
                        return;
                }
        }
        else
        {
                configurator = new PropertyConfigurator();
        }

        configurator->doConfigure(configFileName, hierarchy);
}