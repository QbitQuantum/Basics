int
TAO_Notify_Service_Driver::fini (void)
{
  /// Release all the _vars as the ORB about to go away.
  CosNotifyChannelAdmin::EventChannelFactory_var factory =
    this->notify_factory_._retn ();
  CORBA::ORB_var orb = this->orb_._retn ();
  CORBA::ORB_var dispatching_orb = this->dispatching_orb_._retn ();
  PortableServer::POA_var poa = this->poa_._retn ();
  CosNaming::NamingContextExt_var naming = this->naming_._retn ();

  // This must be called to ensure that all services shut down
  // correctly.  Depending upon the type of service loaded, it may
  // or may not actually perform any actions.
  this->notify_service_->finalize_service (factory.in ());
  factory = CosNotifyChannelAdmin::EventChannelFactory::_nil ();

  this->notify_service_->fini ();

  // Deactivate.
  if (this->use_name_svc_ && !CORBA::is_nil (naming.in ()))
    {
      // Unbind all event channels from the naming service
      if (this->register_event_channel_)
        {
          for (ACE_Unbounded_Set<ACE_CString>::const_iterator ci (
               this->notify_channel_name_); !ci.done(); ci++)
            {
              CosNaming::Name_var name = naming->to_name ((*ci).c_str ());
              naming->unbind (name.in ());
            }
        }

      // Unbind from the naming service.
      CosNaming::Name_var name =
        naming->to_name (this->notify_factory_name_.c_str ());

      naming->unbind (name.in ());

      naming = CosNaming::NamingContextExt::_nil ();
    }

  if (!CORBA::is_nil (poa.in ()))
    {
      poa->destroy (true, true);
      poa = PortableServer::POA::_nil ();
    }

  if (this->shutdown_dispatching_orb_ && !CORBA::is_nil (dispatching_orb_.in ()))
    {
      dispatching_orb->shutdown ();
    }

  // shutdown the ORB.
  if (this->shutdown_orb_ && !CORBA::is_nil (orb.in ()))
    {
      orb->shutdown ();
    }

  // Make sure all worker threads are gone.
  this->worker_.wait ();
  this->logging_worker_.wait ();

  // Destroy the ORB
  if (this->shutdown_dispatching_orb_ && !CORBA::is_nil (dispatching_orb_.in ()))
    {
      dispatching_orb->destroy ();
    }

  // Destroy the ORB.
  if (this->shutdown_orb_ && !CORBA::is_nil (orb.in ()))
    {
      orb->destroy ();
    }

  dispatching_orb_ = CORBA::ORB::_nil ();

  worker_.orb (CORBA::ORB::_nil ());

  orb = CORBA::ORB::_nil ();

  return 0;
}