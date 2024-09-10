CORBA::Object_ptr
TAO_Trading_Loader::create_object (CORBA::ORB_ptr orb_ptr,
                                   int argc,
                                   ACE_TCHAR *argv[])
{
  // Duplicate the ORB
  CORBA::ORB_var orb = CORBA::ORB::_duplicate (orb_ptr);

  // Activating the poa manager
  this->orb_manager_.activate_poa_manager ();

  // Create a Trader Object and set its Service Type Repository.
  auto_ptr<TAO_Trader_Factory::TAO_TRADER> auto_trader (TAO_Trader_Factory::create_trader (argc, argv));

  this->trader_ = auto_trader;

  TAO_Support_Attributes_i &sup_attr =
    this->trader_->support_attributes ();

  TAO_Trading_Components_i &trd_comp =
    this->trader_->trading_components ();

  sup_attr.type_repos (this->type_repos_._this ());

  // The Spec says: return a reference to the Lookup interface from
  // the resolve_initial_references method.
  CosTrading::Lookup_ptr lookup =
    trd_comp.lookup_if ();

  this->ior_ =
    orb->object_to_string (lookup);

  // Parse the args
  if (this->parse_args (argc, argv) == -1)
    return CORBA::Object::_nil ();

  // Dump the ior to a file.
  if (this->ior_output_file_ != 0)
    {
      ACE_OS::fprintf (this->ior_output_file_,
                       "%s",
                       this->ior_.in ());
      ACE_OS::fclose (this->ior_output_file_);
    }

  CORBA::Object_var table_object =
    orb->resolve_initial_references ("IORTable");

  IORTable::Table_var adapter =
    IORTable::Table::_narrow (table_object.in ());

  if (CORBA::is_nil (adapter.in ()))
    {
      ORBSVCS_ERROR ((LM_ERROR, "Nil IORTable\n"));
    }
  else
    {
      adapter->bind ("TradingService",
                     this->ior_.in ());
    }

  if (this->federate_)
    {
      // Only become a multicast server if we're the only trader
      // on the multicast network.
      // @@ Could do other things. For example, every timeout
      // period try to federate again, but let's not hardcode that
      // policy.
      int rc = this->bootstrap_to_federation ();

      if (rc == -1)
        this->init_multicast_server ();
    }
  else
    this->init_multicast_server ();

  return CORBA::Object::_nil ();
}