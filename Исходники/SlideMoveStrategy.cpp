void SlideMoveStrategy::configure(jccl::ConfigElementPtr cfgElt)
{
   vprASSERT(cfgElt->getID() == getElementType());

   const unsigned int req_cfg_version(2);

   if ( cfgElt->getVersion() < req_cfg_version )
   {
      std::stringstream msg;
      msg << "Configuration of SlideMoveStrategy failed.  Required config "
          << "element version is " << req_cfg_version << ", but element '"
          << cfgElt->getName() << "' is version " << cfgElt->getVersion();
      throw PluginException(msg.str(), VRKIT_LOCATION);
   }

   const std::string slide_target_prop("slide_target");
   const std::string analog_input_prop("analog_input");
   const std::string forward_value_prop("forward_slide_value");
   const std::string slide_epsilon_prop("slide_epsilon");

   const unsigned int slide_target =
      cfgElt->getProperty<unsigned int>(slide_target_prop);

   if ( slide_target == 0 || slide_target == 1 )
   {
      mSlideTarget = static_cast<SlideTarget>(slide_target);
   }
   else
   {
      VRKIT_STATUS << "ERROR: Invalid slide target identifier "
                   << slide_target << std::endl;
   }

   const int analog_num = cfgElt->getProperty<int>(analog_input_prop);

   // -1 disables sliding. Otherwise, the analog number must be in the range
   // 0 <= analog_num < 4.
   if ( analog_num == -1 || 0 <= analog_num && analog_num < 4 )
   {
      mAnalogNum = analog_num;
   }
   else
   {
      VRKIT_STATUS << "ERROR: Analog input index (" << analog_num
                   << ") given!\n"
                   << "This must be -1 (to disable) or in the range [0, 4)."
                   << std::endl;
   }

   const float fwd_val = cfgElt->getProperty<float>(forward_value_prop);

   if ( fwd_val == 0.0f || fwd_val == 1.0f )
   {
      mForwardValue = fwd_val;
   }
   else
   {
      VRKIT_STATUS << "ERROR: Invalid forward sliding value (" << fwd_val
                   << ") given!\n"
                   << "This must be either 0.0 or 1.0" << std::endl;
   }

   const float eps = cfgElt->getProperty<float>(slide_epsilon_prop);

   if ( eps >= 0.0f )
   {
      mSlideEpsilon = eps;
   }
   else
   {
      VRKIT_STATUS << "ERROR: Slide epsilon must be non-negative!"
                   << std::endl;
   }
}