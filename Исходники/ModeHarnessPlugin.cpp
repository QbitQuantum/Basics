void ModeHarnessPlugin::configure(jccl::ConfigElementPtr elt)
{
   vprASSERT(elt->getID() == getElementType());

   const unsigned int req_cfg_version(2);

   // Check for correct version of plugin configuration.
   if ( elt->getVersion() < req_cfg_version )
   {
      std::stringstream msg;
      msg << "Configuration of ModeHarnessPlugin failed.  Required config "
          << "element version is " << req_cfg_version << ", but element '"
          << elt->getName() << "' is version " << elt->getVersion();
      throw PluginException(msg.str(), VRKIT_LOCATION);
   }

   const std::string component_path_prop("component_path");
   const std::string default_component_prop("default_component");
   const std::string component_prop("component");
   const std::string plugin_prop("plugin");
   const std::string signal_prop("signal");
   const std::string active_component_prop("active_component");

   // Set up two default search paths:
   //    1. Relative path to './plugins/mode'
   //    2. VRKIT_BASE_DIR/lib/vrkit/plugins/mode
   //
   // In all of the above cases, the 'debug' subdirectory is searched first if
   // this is a debug build (i.e., when VRKIT_DEBUG is defined and _DEBUG is
   // not).
   std::vector<std::string> component_path =
      plugin::getDefaultSearchPath("mode");

   const unsigned int num_plugin_paths(elt->getNum(component_path_prop));
   for ( unsigned int i = 0; i < num_plugin_paths; ++i )
   {
      std::string dir = elt->getProperty<std::string>(component_path_prop, i);
      component_path.push_back(vpr::replaceEnvVars(dir));
   }

   mDefaultComponentName =
      elt->getProperty<std::string>(default_component_prop);

   const unsigned int num_comps(elt->getNum(component_prop));
   for ( unsigned int i = 0; i < num_comps; ++i )
   {
      jccl::ConfigElementPtr comp_elt =
         elt->getProperty<jccl::ConfigElementPtr>(component_prop, i);
      mComponentInfo.push_back(
         ComponentInfo(comp_elt->getName(),
                       comp_elt->getProperty<std::string>(plugin_prop))
      );
   }

   const unsigned int num_signals(elt->getNum(signal_prop));
   for ( unsigned int i = 0; i < num_signals; ++i )
   {
      jccl::ConfigElementPtr signal_elt =
         elt->getProperty<jccl::ConfigElementPtr>(signal_prop, i);
      mSignalDefs.push_back(
         SignalDef(signal_elt->getName(),
                   signal_elt->getProperty<std::string>(active_component_prop))
      );
   }

   std::vector<vpr::LibraryPtr> modules = plugin::findModules(component_path);
   std::for_each(modules.begin(), modules.end(),
                 boost::bind(&ModeHarnessPlugin::registerModule, this, _1));
}