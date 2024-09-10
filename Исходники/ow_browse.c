/* Sent back from Bounjour -- arbitrarily use it to set the Ref for Deallocation */
static void BrowseBack(DNSServiceRef s, DNSServiceFlags f, uint32_t i, DNSServiceErrorType e, const char *name, const char *type, const char *domain, void *context)
{
	struct BrowseStruct *browse_struct;
	(void) context;
	LEVEL_DETAIL("ref=%ld flags=%d index=%d, error=%d name=%s type=%s domain=%s", (long int) s, f, i, e, name, type, domain);

	if (e != kDNSServiceErr_NoError) {
		return ;
	}

	browse_struct = Browse_Struct_Create( name, type, domain ) ;

	if (f & kDNSServiceFlagsAdd) {	// Add
		DNSServiceRef sr;

		if (DNSServiceResolve(&sr, 0, 0, name, type, domain, ResolveBack, (void *)browse_struct) == kDNSServiceErr_NoError) {
			ResolveWait(sr) ;
			DNSServiceRefDeallocate(sr);
		} else {
			Browse_Struct_Destroy(browse_struct) ;
		}
	} else { // Remove
		Browse_Struct_Destroy(browse_struct) ;
		ZeroDel( name, type, domain ) ;
	}
}