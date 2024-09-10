Speech::~Speech()
{
#ifdef DEBUG
  cout << "Destructing Speech." << endl;
#endif
  //  pConsumer->disconnect_push_consumer();

  try {
    CosNaming::Name n;
     
    n.length(1);
    n[0].id = CORBA::string_dup("Speech");
    namingContext->unbind(n);
    //    n[0].id = CORBA::string_dup("SpeechEC");
    //    namingContext->unbind(n);

#ifdef DEBUG
    cout << "Unbound objects from NamingSevice." << endl;
#endif
  }
  catch (const CORBA::Exception& e) {
    cerr << "Caught CORBA exception on unbind: " << e << endl;
    cerr << "Porbably the NameSevice went down while we ran." << endl;
  }
}