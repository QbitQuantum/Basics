   void CBasicQualifier::AddEventToDatabase(const boost::shared_ptr<const shared::plugin::information::IInformation> pluginInformation,
                                            database::entities::EEventType eventType,
                                            const std::string& reason) const
   {
      try
      {
         // Add event into plugin event logger table
         m_pluginLogger->addEvent(
            pluginInformation->getType(),
            pluginInformation->getVersion(),
            pluginInformation->getReleaseType(),
            eventType,
            reason);

         // Only crashes have to be logged in the main event logger table
         if (eventType == database::entities::EEventType::kCrash)
            m_mainLogger->addEvent(database::entities::ESystemEventCode::kPluginCrash, "plugin " + pluginInformation->getIdentity(), reason);
      }
      catch (shared::exception::CEmptyResult& e)
      {
         // Just log the error
         YADOMS_LOG(error) << "Error when adding plugin " << eventType << " event in database : " << e.what();
      }
   }