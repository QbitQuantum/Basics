/*
 * Class:     sun_security_krb5_Credentials
 * Method:    acquireDefaultNativeCreds
 * Signature: ()Lsun/security/krb5/Credentials;
 */
JNIEXPORT jobject JNICALL Java_sun_security_krb5_Credentials_acquireDefaultNativeCreds(
		JNIEnv *env,
		jclass krbcredsClass) {

   HANDLE LogonHandle = NULL;
   ULONG PackageId;
	PKERB_RETRIEVE_TKT_REQUEST CacheRequest = NULL;
	PKERB_RETRIEVE_TKT_RESPONSE CacheResponse = NULL;
	ULONG rspSize = 0;
	DWORD errorCode;
	NTSTATUS Status,SubStatus;
	PUCHAR pEncodedTicket = NULL;
	jobject ticket, clientPrincipal, targetPrincipal, encryptionKey;
	jobject ticketFlags, startTime, endTime, krbCreds = NULL;
   jobject authTime, renewTillTime, hostAddresses = NULL;
	UNICODE_STRING Target = {0};
	UNICODE_STRING Target2 = {0};
	PDOMAIN_CONTROLLER_INFO DomainControllerInfo = NULL;
	WCHAR *tgtName = L"krbtgt";
	WCHAR *fullName;

	while (TRUE) {

	if (krbcredsConstructor == 0) {
		krbcredsConstructor = (*env)->GetMethodID(env, krbcredsClass, "<init>", 
       "(Lsun/security/krb5/internal/Ticket;Lsun/security/krb5/PrincipalName;Lsun/security/krb5/PrincipalName;Lsun/security/krb5/EncryptionKey;Lsun/security/krb5/internal/TicketFlags;Lsun/security/krb5/internal/KerberosTime;Lsun/security/krb5/internal/KerberosTime;Lsun/security/krb5/internal/KerberosTime;Lsun/security/krb5/internal/KerberosTime;Lsun/security/krb5/internal/HostAddresses;)V");
		if (krbcredsConstructor == 0) {
			printf("Couldn't find com.ibm.security.krb5.Credentials constructor\n");
			break;
		}
	}

	//printf("Found KrbCreds constructor\n");

    //
    // Get the logon handle and package ID from the
    // Kerberos package
    //
    if(!PackageConnectLookup(&LogonHandle, &PackageId))
        break;

	#ifdef DEBUG
	printf("Got handle to Kerberos package\n");
   #endif /* DEBUG */

	//InitUnicodeString(&Target2, L"krbtgt"); // this doesn't work 'cause I need the domain name too
	// OK, I don't give up that easily
	// Go get the current domain name
	errorCode = DsGetDcName(
					(LPCTSTR) NULL, // machine name
					(LPCTSTR) NULL, // DomainName, if NULL, I'm asking what it is
					(GUID *)  NULL, // DomainGuid,
					(LPCTSTR) NULL, // SiteName,
					DS_GC_SERVER_REQUIRED, //Flags
					&DomainControllerInfo);
	if (errorCode != NO_ERROR) {
		printf("DsGetDcName returned %d\n", errorCode);
		break;
	}

	#ifdef DEBUG
	printf("The domain name is %S\n", DomainControllerInfo->DomainName);
   #endif /* DEBUG */
	// Build a fully-qualified name
	fullName = (WCHAR *) LocalAlloc(LMEM_ZEROINIT,((wcslen(tgtName)+wcslen(L"/")+wcslen(DomainControllerInfo->DomainName)) * sizeof(WCHAR) + sizeof(UNICODE_NULL)));
	wcscat(fullName, tgtName);
	wcscat(fullName, L"/");
	wcscat(fullName, DomainControllerInfo->DomainName);
	#ifdef DEBUG
	printf("The fully-qualified name is %S\n", fullName);
   #endif /* DEBUG */
	InitUnicodeString(&Target2, fullName);       

    CacheRequest = (PKERB_RETRIEVE_TKT_REQUEST)
            LocalAlloc(LMEM_ZEROINIT, Target2.Length + sizeof(KERB_RETRIEVE_TKT_REQUEST));

    CacheRequest->MessageType = KerbRetrieveEncodedTicketMessage ;
 
    Target.Buffer = (LPWSTR) (CacheRequest + 1);
    Target.Length = Target2.Length;
    Target.MaximumLength = Target2.MaximumLength;

    CopyMemory(
        Target.Buffer,
        Target2.Buffer,
        Target2.Length
        );

    CacheRequest->TargetName = Target;	
    CacheRequest->EncryptionType = KERB_ETYPE_DES_CBC_MD5; // mdu

	Status = LsaCallAuthenticationPackage(
                LogonHandle,
                PackageId,
                CacheRequest,
                Target2.Length + sizeof(KERB_RETRIEVE_TKT_REQUEST),
                (PVOID *) &CacheResponse,
                &rspSize,
                &SubStatus
                );

	#ifdef DEBUG
	printf("Response size is %d\n", rspSize);
   #endif /* DEBUG */
	LocalFree(fullName);

	if (!LSA_SUCCESS(Status) || !LSA_SUCCESS(SubStatus))
    {
        if (!LSA_SUCCESS(Status)) {
			ShowNTError("LsaCallAuthenticationPackage", Status);
		}
		else {
			ShowNTError("Protocol status", SubStatus);
		}
		break;
    }

	// Now we need to skip over most of the junk in the buffer to get to the ticket
	// Here's what we're looking at...

/*

typedef struct _KERB_RETRIEVE_TKT_RESPONSE {
    KERB_EXTERNAL_TICKET Ticket;
} KERB_RETRIEVE_TKT_RESPONSE, *PKERB_RETRIEVE_TKT_RESPONSE;

typedef struct _KERB_EXTERNAL_TICKET {
    PKERB_EXTERNAL_NAME ServiceName;
    PKERB_EXTERNAL_NAME TargetName;
    PKERB_EXTERNAL_NAME ClientName;
    UNICODE_STRING DomainName;
    UNICODE_STRING TargetDomainName;
    UNICODE_STRING AltTargetDomainName;
    KERB_CRYPTO_KEY SessionKey;
    ULONG TicketFlags;
    ULONG Flags;
    LARGE_INTEGER KeyExpirationTime;
    LARGE_INTEGER StartTime;
    LARGE_INTEGER EndTime;
    LARGE_INTEGER RenewUntil;
    LARGE_INTEGER TimeSkew;
    ULONG EncodedTicketSize;
    PUCHAR EncodedTicket;					<========== Here's the good stuff
} KERB_EXTERNAL_TICKET, *PKERB_EXTERNAL_TICKET;

typedef struct _KERB_EXTERNAL_NAME {
    SHORT NameType;
    USHORT NameCount;
    UNICODE_STRING Names[ANYSIZE_ARRAY];
} KERB_EXTERNAL_NAME, *PKERB_EXTERNAL_NAME;

typedef struct _LSA_UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING;

typedef LSA_UNICODE_STRING UNICODE_STRING, *PUNICODE_STRING;

typedef struct KERB_CRYPTO_KEY {
    LONG KeyType;
    ULONG Length;
    PUCHAR Value;
} KERB_CRYPTO_KEY, *PKERB_CRYPTO_KEY;

*/

	// Build a com.ibm.security.krb5.Ticket
	ticket = BuildTicket(env, CacheResponse->Ticket.EncodedTicket, CacheResponse->Ticket.EncodedTicketSize);
	if (ticket == NULL) {
		break;
	}
	// OK, have a Ticket, now need to get the client name
	clientPrincipal = BuildClientPrincipal(env, CacheResponse->Ticket.ClientName); // mdu
	if (clientPrincipal == NULL) break;
	// and the "name" of tgt
	targetPrincipal = BuildTGSPrincipal(env, CacheResponse->Ticket.TargetDomainName); // mdu
	if (targetPrincipal == NULL) break;
	// Get the encryption key
	encryptionKey = BuildEncryptionKey(env, &(CacheResponse->Ticket.SessionKey));
	if (encryptionKey == NULL) break;
	// and the ticket flags
	ticketFlags = BuildTicketFlags(env, &(CacheResponse->Ticket.TicketFlags));
	if (ticketFlags == NULL) break;
	// Get the start time
	startTime = BuildKerberosTime(env, &(CacheResponse->Ticket.StartTime));
	if (startTime == NULL) break;
	/*
	 * mdu: No point storing the eky expiration time in the auth
	 * time field. Set it to be same as startTime. Looks like
	 * windows does not have post-dated tickets.
	 */
	authTime = startTime;
	// and the end time
	endTime = BuildKerberosTime(env, &(CacheResponse->Ticket.EndTime));
	if (endTime == NULL) break;
	// Get the renew till time
	renewTillTime = BuildKerberosTime(env, &(CacheResponse->Ticket.RenewUntil));
	if (renewTillTime == NULL) break;
	// and now go build a KrbCreds object
	krbCreds = (*env)->NewObject(
		env,
		krbcredsClass,
		krbcredsConstructor,
		ticket,
		clientPrincipal,
		targetPrincipal,
		encryptionKey,
		ticketFlags,
		authTime, // mdu
		startTime,
		endTime,
		renewTillTime, //mdu
		hostAddresses);
	break;
	} // end of WHILE

	if (DomainControllerInfo != NULL) {
		NetApiBufferFree(DomainControllerInfo);
	}
    if (CacheResponse != NULL) {
        LsaFreeReturnBuffer(CacheResponse);
    }
    if (CacheRequest) {
        LocalFree(CacheRequest);
    }
	return krbCreds;
}