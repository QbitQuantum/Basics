void UmlUseCase::importIt(FileIn & in, Token & token, UmlItem * where)
{
  where = where->container(anUseCase, token, in);
    
  if (where != 0) {
    Q3CString s = token.valueOf("name");
    
    if (s.isEmpty()) {
      static unsigned n = 0;
      
      s.sprintf("anonymous_usecase_%u", ++n);
    }
    
    UmlUseCase * uc = create(where, s);
    
    if (uc == 0)
      in.error("cannot create use case '" + s +
	       "' in '" + where->name() + "'");
    
    uc->addItem(token.xmiId(), in);
    
    if (! token.closed()) {
      Q3CString k = token.what();
      const char * kstr = k;
      
      while (in.read(), !token.close(kstr))
	uc->UmlItem::import(in, token);
    }

    uc->unload(TRUE, FALSE);
  }
}