void KFMExec::slotMimeType( const char *_type )
{
    // A dirty hack for passing the character set
    char *typestr=0;
    const char *aType=0;
    const char *aCharset=0;
    if ( _type )
    {
        typestr=new char[strlen(_type)+1];
        strcpy(typestr,_type);
	aType=strtok(typestr," ;\t\n");
	char *tmp;
	while((tmp=strtok(0," ;\t\n"))){
            if ( strncmp(tmp,"charset=",8)==0 ) aCharset=tmp+8;
	}    
	if ( aCharset != 0 )
	{
	    tmp=strpbrk((char*)aCharset," ;\t\n");
	    if ( tmp != 0 ) *tmp=0;
	}    
    }  
    
    // Stop browsing. We need an application
    job->stop();
    // delete job;
    // job = 0L;
    
    // GZIP
    if ( aType && strcmp( aType, "application/x-gzip" ) == 0L )
    {
	job->stop();
	tryURL += "#gzip:/";
	openURL( tryURL );
    }
    // TAR
    else if ( aType && strcmp( aType, "application/x-tar" ) == 0L )
    {
	// Is this tar file perhaps hosted in a gzipped file ?
	KURL u( tryURL );
	// ... then we already have a 'gzip' subprotocol
	if ( u.hasSubProtocol() )
	{
	    KURL u2( u.nestedURL() );
	    if ( strcmp( u2.protocol(), "gzip" ) == 0 )
	    {
		// Remove the 'gzip' protocol. It will only slow down the process,
		// since two subprotocols '#gzip:/#tar:/' are not very fast
		// right now.
		tryURL = u.parentURL();
	    }
	}
	
	job->stop();
	tryURL += "#tar:/";
	openURL( tryURL );
    }
    // No HTML ?
    else if ( aType == 0L || strcmp( aType, "text/html" ) != 0L )
    {
      bool bdone = false;
      // Do we know the mime type ?
      if ( aType != 0L )
      {
	KMimeType *mime = KMimeType::findByName( aType );
	// Try to run the URL if we know the mime type
	if ( mime && mime->run( tryURL ) )
	{
	  // We are a zombie now
	  prepareToDie();
	  bdone = true;
	}
      }
		
      if ( !bdone )
      {    
	// Ask the user what we should do
	OpenWithDlg l( klocale->translate("Open With:"), "", 0L, true );
	if ( l.exec() )
	{
	  KMimeBind *bind = l.mimeBind();
	  if ( bind )
	  {
	    bind->runBinding( tryURL );
	  }
	  else
	  {
	    QString pattern = l.getText();
	    // The user did not something ?
	    if ( !pattern.isEmpty() )
	    {
	      QStrList list;
	      list.append( tryURL );
	      openWithOldApplication( pattern, list );
	    }

	    // We are a zombie now
	    prepareToDie();
	  }	
	}
      }
    }
    // It is HTML
    else
    {
	// Ok, lets open a new window
	KfmGui *m = new KfmGui( 0L, 0L, tryURL );
	if ( aCharset != 0 ) m->setCharset(aCharset);
	if ( dlg )
	  {
	    delete dlg;
	    dlg = 0L;
	  }
	m->show();
	
	// We are a zombie now
	prepareToDie();
    }
    delete typestr;
}