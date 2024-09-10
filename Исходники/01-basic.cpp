void t01_basic(){
  INIT_LOCAL()
  
  Onion::Onion o;
  MyHandler m;

  Onion::Url url(o);
  
  url.add("", handler);
  url.add("static", "Estatico");
  url.add<MyHandler>("m", &m, &MyHandler::index);
  
  o.setInternalErrorHandler( new Onion::HandlerMethod<MyHandler>(&m, &MyHandler::error) );
  
  o.listen();
  
  END_LOCAL()
}