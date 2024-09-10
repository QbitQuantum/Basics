NotifyLogPlayer::~NotifyLogPlayer()
{
  DBG(cout << "Destructing NotifyLogPlayer." << endl);

  delete pPushSupplier;

  try {
    if (own_) {
      CosNaming::Name n;
      n.length(1);
      n[0].id = CORBA::string_dup("EventChannel");
      namingContext->unbind(n);
    }
    if (colocated_)
      initialNamingContext->unbind(channelFactoryName);

  }
  catch (const CORBA::Exception& e) {
    cerr << "Caught CORBA exception on unbind: " << e << endl;
    cerr << "Porbably the NameSevice went down while we run." << endl;
  }

  DBG(cout << "unbound objects from Name Sevice" << endl);

  if (colocated_)
    ec_->destroy();
}