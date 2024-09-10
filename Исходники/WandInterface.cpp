void WandInterface::configure(jccl::ConfigElementPtr elt)
{
   vprASSERT(elt->getID() == getElementType());

   const unsigned int req_cfg_version(1);

   if ( elt->getVersion() < req_cfg_version )
   {
      std::ostringstream msg;
      msg << "Configuration of WandInterface failed.  Required config "
          << "element version is " << req_cfg_version << ", but element '"
          << elt->getName() << "' is version " << elt->getVersion();
      throw Exception(msg.str(), VRKIT_LOCATION);
   }

   const std::string pos_name_prop("position_name");
   const std::string digital_name_prop("digital_name");
   const std::string analog_name_prop("analog_name");

   const std::string wand_name = elt->getProperty<std::string>(pos_name_prop);

   if ( wand_name.empty() )
   {
      throw Exception("Empty wand name is not allowed", VRKIT_LOCATION);
   }

   mWandInterface.init(wand_name);

   const unsigned int num_digitals(elt->getNum(digital_name_prop));

   if ( num_digitals > 0 )
   {
      mButtonInterfaces.resize(num_digitals);

      for ( unsigned int d = 0; d < num_digitals; ++d )
      {
         const std::string digital_name =
            elt->getProperty<std::string>(digital_name_prop, d);

         if ( digital_name.empty() )
         {
            mButtonInterfaces.clear();

            std::ostringstream msg_stream;
            msg_stream << "Empty digital name (index " << d
                       << ") is not allowed";
            throw Exception(msg_stream.str(), VRKIT_LOCATION);
         }

         mButtonInterfaces[d].init(digital_name);
      }
   }

   const unsigned int num_analogs(elt->getNum(analog_name_prop));

   if ( num_analogs > 0 )
   {
      mAnalogInterfaces.resize(num_analogs);

      for ( unsigned int a = 0; a < num_analogs; ++a )
      {
         const std::string analog_name =
            elt->getProperty<std::string>(analog_name_prop, a);

         if ( analog_name.empty() )
         {
            mAnalogInterfaces.clear();

            std::ostringstream msg_stream;
            msg_stream << "Empty analog name (index " << a
                       << ") is not allowed";
            throw Exception(msg_stream.str(), VRKIT_LOCATION);
         }

         mAnalogInterfaces[a].init(analog_name);
      }
   }
}