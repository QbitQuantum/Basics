// Configure the MotionStar with the given config element.
bool MotionStar::config(jccl::ConfigElementPtr e)
{
   bool retval(false);

   if ( Input::config(e) &&  Position::config(e) )
   {
      vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_STATE_LVL)
         << "MotionStar::config(jccl::ConfigElementPtr)\n"
         << vprDEBUG_FLUSH;

      const unsigned int cur_version(2);

      if ( e->getVersion() < cur_version )
      {
         vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
            << clrOutBOLD(clrRED, "ERROR")
            << " [gadget::MotionStar::config()] Element named '"
            << e->getName() << "'" << std::endl << vprDEBUG_FLUSH;
         vprDEBUG_NEXT(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
            << "is version " << e->getVersion()
            << ", but we require at least version " << cur_version
            << std::endl << vprDEBUG_FLUSH;
         vprDEBUG_NEXT(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
            << "Ignoring this element and moving on." << std::endl
            << vprDEBUG_FLUSH;
         retval = false;
      }
      else
      {
         // Configure mMotionStar with the config info.
         const unsigned num_filters = e->getNum("position_filters");

         // Sanity check.  There has to be at least one position filter
         // configured.
         if ( num_filters == 0 )
         {
            vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
               << clrOutBOLD(clrRED, "ERROR")
               << ": [MotionStar::config(jccl::ConfigElementPtr)] No position "
               << "filters configured in " << e->getName() << std::endl
               << vprDEBUG_FLUSH;
            retval = false;
         }
         else
         {
            BIRDNET::units expected_units;

            // Find the first position_transform_filter instance and get its
            // device_units property value.  This will tell us what units we're
            // expecting from the hardware.
            const std::string filter_type("position_transform_filter");
            for ( unsigned i = 0; i < num_filters; ++i )
            {
               jccl::ConfigElementPtr pos_elt =
                  e->getProperty<jccl::ConfigElementPtr>("position_filters", i);

               if ( pos_elt->getID() == filter_type )
               {
                  const float unit_conv =
                     pos_elt->getProperty<float>("device_units");

                  vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_VERB_LVL)
                     << "[gadget::MotionStar::config()] Read " << unit_conv
                     << " as the conversion from device units to meters.\n"
                     << vprDEBUG_FLUSH;

                  // Inches.  This is the most likely configuration as of this
                  // writing.
                  if ( unit_conv == 0.0254f )
                  {
                     expected_units = BIRDNET::INCHES;
                  }
                  // Feet.
                  else if ( unit_conv == 0.3048f )
                  {
                     expected_units = BIRDNET::FEET;
                  }
                  // Meters.
                  else if ( unit_conv == 1.0f )
                  {
                     expected_units = BIRDNET::METERS;
                  }
                  // Unexpected value.
                  else
                  {
                     vprDEBUG(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
                        << "[MotionStar::config(jccl::ConfigElementPtr)] "
                        << clrOutBOLD(clrRED, "ERROR")
                        << ": Unsupported device unit value " << unit_conv
                        << " in " << pos_elt->getFullName() << std::endl
                        << vprDEBUG_FLUSH;
                     vprDEBUG_NEXT(gadgetDBG_INPUT_MGR, vprDBG_CRITICAL_LVL)
                        << "Check your configuration for errors.\n"
                        << vprDEBUG_FLUSH;

                     // Break out of this method early because the
                     // configuration element we were given is bad.
                     return false;
                  }

                  // We're done checking for unit conversion values.
                  break;
               }
            }

            mMotionStar.setExpectedUnits(expected_units);

            setAddressName(e->getProperty<std::string>("address").c_str());
            setServerPort((unsigned short) e->getProperty<int>("server_port"));
            setMasterStatus(e->getProperty<bool>("is_master"));
            setHemisphere((unsigned char) e->getProperty<int>("hemisphere"));
            setBirdFormat((unsigned int) e->getProperty<int>("data_format"));
            setRunMode((unsigned int) e->getProperty<int>("mode"));
            setReportRate((unsigned char) e->getProperty<int>("report_rate"));
            setMeasurementRate(e->getProperty<float>("measurement_rate"));
            retval = true;
         }
      }
   }

   return retval;
}