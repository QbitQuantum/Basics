void
Connection_Manager::unbind_sender (const ACE_CString &sender_name,
                                   AVStreams::MMDevice_ptr sender_mmdevice_obj)
{
  if (TAO_debug_level > 0)
    ACE_DEBUG ((LM_DEBUG,
                "Connection_Manager::unbind_sender\n"));

  CosNaming::Name name (1);
  name.length (1);

  // Try binding the sender context in the NS
  name [0].id =
    CORBA::string_dup (sender_name.c_str ());

  try
    {
      CORBA::Object_var object =
        this->naming_client_->resolve (name);

      CosNaming::NamingContext_var sender_context =
        CosNaming::NamingContext::_narrow (object.in ());

      if (TAO_debug_level > 0)
        ACE_DEBUG ((LM_DEBUG,
                    "Sender Context Found\n"));

      try
        {
          object =
            sender_context->resolve (name);

          AVStreams::MMDevice_var mmdevice =
            AVStreams::MMDevice::_narrow (object.in ());

          if (mmdevice->_is_equivalent (sender_mmdevice_obj))
          {
            sender_context->unbind (name);

            if (TAO_debug_level > 0)
              ACE_DEBUG ((LM_DEBUG,
                          "Sender Unbound\n"));
          }
        }
      catch (const CosNaming::NamingContext::NotFound&)
        {
          ACE_DEBUG ((LM_DEBUG,
                      "Sender object not found\n"));
          // Do not have to unbind.
        }

    }
  catch (const CosNaming::NamingContext::NotFound&)
    {
      ACE_DEBUG ((LM_DEBUG,
                  "Sender Context Not Found\n"));
      // Do not have to unbind.
    }

}