   bool CorbaPerfPlugin::configAdd(jccl::ConfigElementPtr element)
   {
      const unsigned int min_def_version(2);

      if ( element->getVersion() < min_def_version )
      {
         vprDEBUG(jcclDBG_PLUGIN, vprDBG_WARNING_LVL)
            << clrOutBOLD(clrYELLOW, "WARNING") << ": Element named '"
            << element->getName() << "'" << std::endl;
         vprDEBUG_NEXTnl(jcclDBG_PLUGIN, vprDBG_WARNING_LVL)
            << "is version " << element->getVersion()
            << ", but we expect at least version " << min_def_version
            << ".\n";
         vprDEBUG_NEXTnl(jcclDBG_PLUGIN, vprDBG_WARNING_LVL)
            << "Default values will be used for some settings.\n"
            << vprDEBUG_FLUSH;
      }

      // If the ORB is already running, we need to shut it down first.  One big
      // reason for doing this is to release the resources (memory and so on)
      // allocated previously.
      if ( mInterface != NULL || mCorbaManager != NULL )
      {
         vprDEBUG(vrjDBG_PLUGIN, vprDBG_STATE_LVL)
            << "[CorbaPerfPlugin::configAdd()] Attempting to shut down "
            << "existing CORBA instance.\n" << vprDEBUG_FLUSH;

         // stopCorba() will call disable() if we are still in the enabled state.
         stopCorba();
      }

      // We'll ignore the return value for now.  startCorba() prints out enough
      // warning information on its own if something goes wrong.
      this->startCorba(element->getProperty<std::string>("endpoint_addr"),
                       element->getProperty<vpr::Uint16>("endpoint_port"));

      return true;
   }