void TerminationSignalHandler(int)
{
     try
	{
	// false - avoid deadlock; true would try to wait for all requests
	// to complete before returning, but because we are calling it from within
	// a request, we would be blocking it from 
	  orb->shutdown(false);
	  
	}
    catch( CORBA::Exception &ex )
	{
	ex._tao_print_exception("TerminationSignalHandler");
	}
}