/////////////////////////////////////////////////////////////////////////////
// HRESULT CMallocSpy::Unregister
//
/////////////////////////////////////////////////////////////////////////////
HRESULT CMallocSpy::Unregister()
{
	//NOTE:  Unregister will fail if their are outstanding leaks as the docs indicate:
	
	//If the return code is E_ACCESSDENIED, there are still outstanding allocations that were 
	//made while the spy was active. In this case, the registered spy cannot be revoked at this 
	//time because it may have attached arbitrary headers and/or trailers to these allocations 
	//that only the spy knows about. Only the spy's PreFree (or PreRealloc) method knows how to 
	//account for these headers and trailers. Before returning E_ACCESSDENIED, CoRevokeMallocSpy 
	//notes internally that a revoke is pending. When the outstanding allocations have been freed, 
	//the revoke proceeds automatically, releasing the IMallocSpy object. Thus, it is necessary to
	//call CoRevokeMallocSpy only once for each call to CoRegisterMallocSpy, even if E_ACCESSDENIED
	//is returned.
	return CoRevokeMallocSpy(); //Does a Release on Object
}