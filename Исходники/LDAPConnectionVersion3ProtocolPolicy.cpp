void LDAPConnectionVersion3ProtocolPolicy::setProtocolVersion(LDAP* ldap) {
	unsigned long version = LDAP_VERSION3;
	int iRtn = ldap_set_option(ldap, LDAP_OPT_PROTOCOL_VERSION, (void*)&version);
	if(iRtn != LDAP_SUCCESS) {
		std::ostringstream buffer;
		buffer << "LDAP version setting failed: ";

		ULONG errorCode = LdapGetLastError();
		ULONG win32ErrorCode = LdapMapErrorToWin32(errorCode);

		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			win32ErrorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		std::string win32Message((LPCTSTR)lpMsgBuf);
		LocalFree( lpMsgBuf );

		buffer << " " << win32Message;

		switch(iRtn) {
			case LDAP_ADMIN_LIMIT_EXCEEDED:
				throw LDAPAdminLimitExceededException(buffer.str());
			
			case LDAP_AFFECTS_MULTIPLE_DSAS:
				throw LDAPAffectsMultipleDsasException(buffer.str());
			
			case LDAP_ALIAS_DEREF_PROBLEM:
				throw LDAPAliasDerefProblemException(buffer.str());
			
			case LDAP_ALIAS_PROBLEM:
				throw LDAPAliasProblemException(buffer.str());
			
			case LDAP_ALREADY_EXISTS:
				throw LDAPAlreadyExistsException(buffer.str());
			
			case LDAP_ATTRIBUTE_OR_VALUE_EXISTS:
				throw LDAPAttributeOrValueExistsException(buffer.str());
			
			case LDAP_AUTH_METHOD_NOT_SUPPORTED:
				throw LDAPAuthMethodNotSupportedException(buffer.str());
			
			case LDAP_AUTH_UNKNOWN:
				throw LDAPAuthUnknownException(buffer.str());
			
			case LDAP_BUSY:
				throw LDAPBusyException(buffer.str());
			
			case LDAP_CLIENT_LOOP:
				throw LDAPClientLoopException(buffer.str());
			
			case LDAP_CONFIDENTIALITY_REQUIRED:
				throw LDAPConfidentialityRequiredException(buffer.str());
			
			case LDAP_CONNECT_ERROR:
				throw LDAPConnectErrorException(buffer.str());
			
			case LDAP_CONSTRAINT_VIOLATION:
				throw LDAPConstraintViolationException(buffer.str());

			case LDAP_CONTROL_NOT_FOUND:
				throw LDAPControlNotFoundException(buffer.str());

			case LDAP_DECODING_ERROR:
				throw LDAPDecodingErrorException(buffer.str());

			case LDAP_ENCODING_ERROR:
				throw LDAPEncodingErrorException(buffer.str());

			case LDAP_FILTER_ERROR:
				throw LDAPFilterErrorException(buffer.str());

			case LDAP_INAPPROPRIATE_AUTH:
				throw LDAPInappropriateAuthException(buffer.str());

			case LDAP_INAPPROPRIATE_MATCHING:
				throw LDAPInappropriateMatchingException(buffer.str());

			case LDAP_INSUFFICIENT_RIGHTS:
				throw LDAPInsufficientRightsException(buffer.str());

			case LDAP_INVALID_CREDENTIALS:
				throw LDAPInvalidCredentialsException(buffer.str());

			case LDAP_INVALID_DN_SYNTAX:
				throw LDAPInvalidDNSyntaxException(buffer.str());

			case LDAP_INVALID_SYNTAX:
				throw LDAPInvalidSyntaxException(buffer.str());

			case LDAP_LOCAL_ERROR:
				throw LDAPLocalErrorException(buffer.str());

			case LDAP_NAMING_VIOLATION:
				throw LDAPNamingViolationException(buffer.str());

			case LDAP_NO_MEMORY:
				throw LDAPNoMemoryException(buffer.str());

			case LDAP_NO_OBJECT_CLASS_MODS:
				throw LDAPNoObjectClassModsException(buffer.str());

			case LDAP_NO_RESULTS_RETURNED:
				throw LDAPNoResultsReturnedException(buffer.str());

			case LDAP_NO_SUCH_ATTRIBUTE:
				throw LDAPNoSuchAttributeException(buffer.str());

			case LDAP_NO_SUCH_OBJECT:
				throw LDAPNoSuchObjectException(buffer.str());

			case LDAP_NOT_ALLOWED_ON_NONLEAF:
				throw LDAPOpNotAllowedOnNonleafException(buffer.str());

			case LDAP_NOT_ALLOWED_ON_RDN:
				throw LDAPOpNotAllowedOnRDNException(buffer.str());

			case LDAP_NOT_SUPPORTED:
				throw LDAPNotSupportedException(buffer.str());

			case LDAP_OBJECT_CLASS_VIOLATION:
				throw LDAPObjectClassViolationException(buffer.str());

			case LDAP_OPERATIONS_ERROR:
				throw LDAPOperationsErrorException(buffer.str());

			case LDAP_OTHER:
				throw LDAPOtherException(buffer.str());

			case LDAP_PARAM_ERROR:
				throw LDAPParamErrorException(buffer.str());

			case LDAP_PROTOCOL_ERROR:
				throw LDAPProtocolErrorException(buffer.str());

			case LDAP_REFERRAL_LIMIT_EXCEEDED:
				throw LDAPReferralLimitExceededException(buffer.str());

			case LDAP_RESULTS_TOO_LARGE:
				throw LDAPResultsTooLargeException(buffer.str());

			case LDAP_SERVER_DOWN:
				throw LDAPServerDownException(buffer.str());

			case LDAP_SIZELIMIT_EXCEEDED:
				throw LDAPSizeLimitExceededException(buffer.str());

			case LDAP_STRONG_AUTH_REQUIRED:
				throw LDAPStrongAuthRequiredException(buffer.str());

			case LDAP_TIMELIMIT_EXCEEDED:
				throw LDAPTimeLimitExceededException(buffer.str());

			case LDAP_TIMEOUT:
				throw LDAPTimeoutException(buffer.str());

			case LDAP_UNAVAILABLE:
				throw LDAPUnavailableException(buffer.str());

			case LDAP_UNAVAILABLE_CRIT_EXTENSION:
				throw LDAPUnavailableCritExtensionException(buffer.str());

			case LDAP_UNDEFINED_TYPE:
				throw LDAPUndefinedTypeException(buffer.str());

			case LDAP_UNWILLING_TO_PERFORM:
				throw LDAPUnwillingToPerformException(buffer.str());

			case LDAP_USER_CANCELLED:
				throw LDAPUserCancelledException(buffer.str());

			case LDAP_VIRTUAL_LIST_VIEW_ERROR:
				throw LDAPVirtualListViewErrorException(buffer.str());
		}
	}
}