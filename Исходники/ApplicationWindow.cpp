void
ApplicationWindow::resolveFactory(QString const& _name)
{
  try {
    CosNaming::Name name;
    
    name.length(1);
    name[0].id = CORBA::string_dup(_name.latin1());
    CosNotifyChannelAdmin::EventChannelFactory_ptr factory =
      server_.resolveName<CosNotifyChannelAdmin::EventChannelFactory>(name);
    
    EventChannelFactory * f = 
      new EventChannelFactory(factory, listView_, this, _name);

    connect(timer_, SIGNAL(timeout()), f, SLOT(updateFactory()));
  }
  catch(CORBA::Exception& e) {
    std::ostringstream sstr;
    sstr << "CORBA exception: " << e << std::flush;

    QString error = sstr.str().c_str();
    QMessageBox::warning(this, 
			 "Resolve EventChannelFactory", 
			 "Error resolving factory " + _name + ".\n" + error);

  }
}