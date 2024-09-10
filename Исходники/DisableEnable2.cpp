int _test(CIMClient& client, const char* opt, String& qlang)
{
  if (String::equalNoCase (opt, "setup"))
  {
    _setup (client, qlang);
  }
  else if (String::equalNoCase (opt, "setup2"))
  {
    _setup2 (client, qlang);
  }
  else if (String::equalNoCase (opt, "create"))
  {
    _create (client);
  }
  else if (String::equalNoCase (opt, "create2"))
  {
    _create2 (client);
  }
  else if (String::equalNoCase (opt, "sendSucceed"))
  {
    _sendSucceed (client);
  }
  else if (String::equalNoCase (opt, "sendFail"))
  {
    _sendFail (client);
  }
  else if (String::equalNoCase (opt, "sendBlock"))
  {
    _sendBlock (client);
  }
  else if (String::equalNoCase (opt, "delete"))
  {
    _delete (client);
  }
  else if (String::equalNoCase (opt, "delete2"))
  {
    _delete2 (client);
  }
  else if (String::equalNoCase (opt, "cleanup"))
  {
    _cleanup (client);
  }
  else if (String::equalNoCase (opt, "cleanup2"))
  {
    _cleanup2 (client);
  }
  else
  {
    PEGASUS_STD (cerr) << "Invalid option: " << opt 
                       << PEGASUS_STD (endl);
    _usage ();
    return -1;
  }
  
  return 0;
}