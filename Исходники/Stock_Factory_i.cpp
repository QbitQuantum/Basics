void
Quoter_Stock_Factory_i::load_stock_objects (
      PortableServer::POA_ptr poa,
      PortableServer::POAManager_ptr poa_manager,
      RtecEventChannelAdmin::SupplierAdmin_ptr supplier_admin)
{
  if (!CORBA::is_nil (this->stock_factory_poa_.in ()))
    return;

  CORBA::PolicyList policies (2);
  policies.length (2);

  policies[0] =
    poa->create_id_assignment_policy (PortableServer::USER_ID);
  policies[1] =
    poa->create_implicit_activation_policy (PortableServer::NO_IMPLICIT_ACTIVATION);

  this->stock_factory_poa_ =
    poa->create_POA ("Stock_Factory_POA",
                     poa_manager,
                     policies);

  for (CORBA::ULong i = 0; i != policies.length (); ++i) {
    policies[i]->destroy ();
  }

  while (!cin.eof () && cin.peek () != EOF) {
    const int max_symbol_length = 8;
    char symbol[max_symbol_length];
    const int max_full_name_length = 64;
    char full_name[max_full_name_length];
    double price;

    cin.getline (symbol, max_symbol_length, '\n');
    cin.getline (full_name, max_full_name_length, '\n');
    cin >> price;
    cin.ignore (1, '\n');

    Quoter_Stock_i *stock =
      new Quoter_Stock_i (symbol, full_name, price);

    PortableServer::ServantBase_var servant = stock;

    PortableServer::ObjectId_var oid =
      PortableServer::string_to_ObjectId (symbol);

    this->stock_factory_poa_->activate_object_with_id (oid.in (),
                                                       servant.in ());
    stock->connect (supplier_admin);
  }
}