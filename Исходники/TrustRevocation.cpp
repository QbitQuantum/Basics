/*
 * This method returns a copy of the mPolicies array which ensures that
 * revocation checking (preferably OCSP, otherwise CRL) will be attempted.
 *
 * If OCSP is already in the mPolicies array, this makes sure the
 * CSSM_TP_ACTION_OCSP_REQUIRE_IF_RESP_PRESENT and CSSM_TP_ACTION_OCSP_SUFFICIENT
 * flags are set. If it's not already in the array, a new policy object is added.
 *
 * If CRL is already in the mPolicies array, this makes sure the
 * CSSM_TP_ACTION_FETCH_CRL_FROM_NET and CSSM_TP_ACTION_CRL_SUFFICIENT flags are
 * set. If it's not already in the array, a new policy object is added.
 *
 * Caller is responsible for releasing the returned policies array.
 */
CFMutableArrayRef Trust::forceRevocationPolicies( 
	uint32 &numAdded, 
	Allocator &alloc,
	bool requirePerCert)
{
	SecPointer<Policy> ocspPolicy;
	SecPointer<Policy> crlPolicy;
	CSSM_APPLE_TP_OCSP_OPT_FLAGS ocspFlags;
	CSSM_APPLE_TP_CRL_OPT_FLAGS crlFlags;
	bool hasOcspPolicy = false;
	bool hasCrlPolicy = false;
	numAdded = 0;
	
	ocspFlags = CSSM_TP_ACTION_OCSP_SUFFICIENT;
	crlFlags = CSSM_TP_ACTION_FETCH_CRL_FROM_NET | CSSM_TP_ACTION_CRL_SUFFICIENT;
	if (requirePerCert) {
		ocspFlags |= CSSM_TP_ACTION_OCSP_REQUIRE_IF_RESP_PRESENT;
		crlFlags |= CSSM_TP_ACTION_REQUIRE_CRL_IF_PRESENT;
	}

	CFIndex numPolicies = (mPolicies) ? CFArrayGetCount(mPolicies) : 0;
	for(CFIndex dex=0; dex<numPolicies; dex++) {
		SecPolicyRef secPol = (SecPolicyRef)CFArrayGetValueAtIndex(mPolicies, dex);
		SecPointer<Policy> pol = Policy::required(SecPolicyRef(secPol));
		const CssmOid &oid = pol->oid();
		const CssmData &optData = pol->value();
		if(oid == CssmOid::overlay(CSSMOID_APPLE_TP_REVOCATION_OCSP)) {
			// make sure OCSP options are set correctly
			CSSM_APPLE_TP_OCSP_OPTIONS *opts = (CSSM_APPLE_TP_OCSP_OPTIONS *)optData.Data;
			if (opts) {
				opts->Flags |= ocspFlags;
			} else {
				CSSM_APPLE_TP_OCSP_OPTIONS newOpts;
				memset(&newOpts, 0, sizeof(newOpts));
				newOpts.Version = CSSM_APPLE_TP_OCSP_OPTS_VERSION;
				newOpts.Flags = ocspFlags;
				CSSM_DATA optData = {sizeof(newOpts), (uint8 *)&newOpts};
				pol->value() = optData;
			}
			hasOcspPolicy = true;
		}
		else if(oid == CssmOid::overlay(CSSMOID_APPLE_TP_REVOCATION_CRL)) {
			// make sure CRL options are set correctly
			CSSM_APPLE_TP_CRL_OPTIONS *opts = (CSSM_APPLE_TP_CRL_OPTIONS *)optData.Data;
			if (opts) {
				opts->CrlFlags |= crlFlags;
			} else {
				CSSM_APPLE_TP_CRL_OPTIONS newOpts;
				memset(&newOpts, 0, sizeof(newOpts));
				newOpts.Version = CSSM_APPLE_TP_CRL_OPTS_VERSION;
				newOpts.CrlFlags = crlFlags;
				CSSM_DATA optData = {sizeof(newOpts), (uint8 *)&newOpts};
				pol->value() = optData;
			}
			hasCrlPolicy = true;
		}
	}	

	/* We're potentially adding something to mPolicies, so make a copy we can work with */
	CFMutableArrayRef policies = CFArrayCreateMutableCopy(NULL, 0, mPolicies);
	if(policies == NULL) {
		throw std::bad_alloc();
	}

	if(!hasOcspPolicy) {
		/* Cook up a new Policy object */
		ocspPolicy = new Policy(mTP, CssmOid::overlay(CSSMOID_APPLE_TP_REVOCATION_OCSP));
		CSSM_APPLE_TP_OCSP_OPTIONS opts;
		memset(&opts, 0, sizeof(opts));
		opts.Version = CSSM_APPLE_TP_OCSP_OPTS_VERSION;
		opts.Flags = ocspFlags;
		
		/* Check prefs dict for local responder info */
		Dictionary *prefsDict = NULL;
		try { /* per-user prefs */
			prefsDict = Dictionary::CreateDictionary(kSecRevocationDomain, Dictionary::US_User, true);
			if (!prefsDict->dict()) {
				delete prefsDict;
				prefsDict = NULL;
			}
		}
		catch(...) {}
		if(prefsDict == NULL) {
			try { /* system prefs */
				prefsDict = Dictionary::CreateDictionary(kSecRevocationDomain, Dictionary::US_System, true);
				if (!prefsDict->dict()) {
					delete prefsDict;
					prefsDict = NULL;
				}
			}
			catch(...) {}
		}
		if(prefsDict != NULL) {
			CFStringRef val = prefsDict->getStringValue(kSecOCSPLocalResponder);
			if(val != NULL) {
				CFDataRef cfData = CFStringCreateExternalRepresentation(NULL,
					val, kCFStringEncodingUTF8, 0);
				CFIndex len = CFDataGetLength(cfData);
				opts.LocalResponder = (CSSM_DATA_PTR)alloc.malloc(sizeof(CSSM_DATA));
				opts.LocalResponder->Data = (uint8 *)alloc.malloc(len);
				opts.LocalResponder->Length = len;
				memmove(opts.LocalResponder->Data, CFDataGetBytePtr(cfData), len);
				CFRelease(cfData);
			}
		}

		/* Policy manages its own copy of the options data */
		CSSM_DATA optData = {sizeof(opts), (uint8 *)&opts};
		ocspPolicy->value() = optData;
		
		/* Policies array retains the Policy object */
		CFArrayAppendValue(policies, ocspPolicy->handle(false));
		numAdded++;
		
		if(prefsDict != NULL)
			delete prefsDict;
	}
	
	if(!hasCrlPolicy) {
		/* Cook up a new Policy object */
		crlPolicy = new Policy(mTP, CssmOid::overlay(CSSMOID_APPLE_TP_REVOCATION_CRL));
		CSSM_APPLE_TP_CRL_OPTIONS opts;
		memset(&opts, 0, sizeof(opts));
		opts.Version = CSSM_APPLE_TP_CRL_OPTS_VERSION;
		opts.CrlFlags = crlFlags;

		/* Policy manages its own copy of this data */
		CSSM_DATA optData = {sizeof(opts), (uint8 *)&opts};
		crlPolicy->value() = optData;
		
		/* Policies array retains the Policy object */
		CFArrayAppendValue(policies, crlPolicy->handle(false));
		numAdded++;
	}

	return policies;
}