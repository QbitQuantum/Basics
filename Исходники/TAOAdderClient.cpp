int main( int argc, char *argv[] )
{
  try 
  {
    // Initialize the CORBA Object Request Broker
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv );

	// Find the CORBA Services Naming Service
	CORBA::Object_var naming_obj = orb->resolve_initial_references("NameService");
	CosNaming::NamingContext_var root = CosNaming::NamingContext::_narrow(naming_obj.in());
	if(CORBA::is_nil(root.in()))
	{
		cerr << "Could not narrow NameService to NamingContext!" << endl;
		throw 0;
	}

    // Resolve the desired object (ExampleInterfaces.IAdder).
	// The module and interface bindings need to be the same here in the client as they
	// are in the server.
    CosNaming::Name name;
    name.length(2);
    name[0].id = CORBA::string_dup( "ExampleInterfaces" );	// IDL-defined Module (namespace)
    name[1].id = CORBA::string_dup( "IAdder" );				// IDL-defined Interface (interface class)
    CORBA::Object_var obj = root->resolve(name);

    // Narrow to confirm that we have the interface we want.
	ExampleInterfaces::IAdder_var iAdder = ExampleInterfaces::IAdder::_narrow(obj.in());
    if (CORBA::is_nil(iAdder.in())) 
	{
      cerr << "Could not narrow to an iAdder reference" << endl;
      return 1;
    }

	// Now use the remote object...
	cout << "Using a remote object that implements the IAdder interface..." << endl;
	cout << endl;
	double number1 = 0;
	double number2 = 0;
	double sum = 0;
	while (true)
	{
		cout << "Enter the first number: ";
		cin >> number1;
		cout << "Enter the second number: ";
		cin >> number2;
		sum = iAdder->add(number1, number2);
		cout << "The sum is: " << sum << endl;
		cout << "------------------" << endl;
	}
  }
  catch ( CORBA::Exception& ex ) {
    cerr << "Caught a CORBA::Exception: " << ex << endl;
    return 1;
  }
  
  return 0;
}