void MultiObjectGrabStrategy::configure(jccl::ConfigElementPtr elt)
{
   vprASSERT(elt->getID() == getElementType());

   const unsigned int req_cfg_version(1);

   // Check for correct version of plugin configuration.
   if ( elt->getVersion() < req_cfg_version )
   {
      std::stringstream msg;
      msg << "Configuration of MultiObjectGrabStrategy failed.  Required "
          << "config element version is " << req_cfg_version
          << ", but element '" << elt->getName() << "' is version "
          << elt->getVersion();
      throw PluginException(msg.str(), VRKIT_LOCATION);
   }

   const std::string choose_btn_prop("choose_button_nums");
   const std::string grab_btn_prop("grab_button_nums");
   const std::string release_btn_prop("release_button_nums");

   mChooseBtn.configure(elt->getProperty<std::string>(choose_btn_prop),
                        mWandInterface);
   mGrabBtn.configure(elt->getProperty<std::string>(grab_btn_prop),
                      mWandInterface);
   mReleaseBtn.configure(elt->getProperty<std::string>(release_btn_prop),
                         mWandInterface);
}