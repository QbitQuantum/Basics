bool Vrpn::config(jccl::ConfigElementPtr e)
{
   const unsigned int min_def_version(2);

   if ( e->getVersion() < min_def_version )
   {
      vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
         << clrOutBOLD(clrYELLOW, "WARNING:") << " Element named '"
         << e->getName() << "'" << std::endl;
      vprDEBUG_NEXTnl(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
         << "is version " << e->getVersion()
         << ", but we expect at least version " << min_def_version
         << ".\n";
      vprDEBUG_NEXTnl(gadgetDBG_INPUT_MGR, vprDBG_WARNING_LVL)
         << "Default values will be used for some settings.\n"
         << vprDEBUG_FLUSH;
   }

   if ( ! (Input::config(e) && Position::config(e) && Digital::config(e) &&
           Analog::config(e)) )
   {
      return false;
   }

   // Get the name of the VRPN tracker server.
   mTrackerServer = e->getProperty<std::string>("tracker_server");
   // Get the number of tracked objects.
   mTrackerNumber = e->getProperty<int>("tracker_count");

   if ( mTrackerNumber > 0 )
   {
      if ( mTrackerServer.empty() )
      {
         vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
            << "[Vrpn::config()] VRPN tracker server name not set!\n"
            << vprDEBUG_FLUSH;
         mTrackerNumber = 0;
      }
      else
      {
         vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CONFIG_LVL)
            << "VRPN driver set to read " << mTrackerNumber
            << " tracker values from '" << mTrackerServer << "'\n"
            << vprDEBUG_FLUSH;
      }

      mPositions.resize(mTrackerNumber);
      mQuats.resize(mTrackerNumber);
   }

   // Get the name of the VRPN button server.
   mButtonServer = e->getProperty<std::string>("button_server");
   // Get the number of buttons.
   mButtonNumber = e->getProperty<int>("button_count");

   if ( mButtonNumber > 0 )
   {
      if ( mButtonServer.empty() )
      {
         vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
            << "[Vrpn::config()] VRPN button server name not set!\n"
            << vprDEBUG_FLUSH;
         mButtonNumber = 0;
      }
      else
      {
         vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CONFIG_LVL)
            << "VRPN driver set to read " << mButtonNumber
            << " button values from '" << mButtonServer << "'\n"
            << vprDEBUG_FLUSH;
      }

      mButtons.resize(mButtonNumber);
   }

   // Get the name of the VRPN analog server.
   mAnalogServer = e->getProperty<std::string>("analog_server");
   // Get the number of analogs.
   mAnalogNumber = e->getProperty<int>("analog_count");

   if ( mAnalogNumber > 0 )
   {
      if ( mAnalogServer.empty() )
      {
         vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
            << "[Vrpn::config()] VRPN analog server name not set!\n"
            << vprDEBUG_FLUSH;
         mAnalogNumber = 0;
      }
      else
      {
         vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CONFIG_LVL)
            << "VRPN driver set to read " << mAnalogNumber
            << " analog values from '" << mAnalogServer << "'\n"
            << vprDEBUG_FLUSH;
      }

      mAnalogs.resize(mAnalogNumber);
   }

   return true;
}