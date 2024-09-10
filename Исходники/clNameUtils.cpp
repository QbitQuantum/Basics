void CL_nssGeneralNameToCssm(
	NSS_GeneralName &nssObj,
	CE_GeneralName &cdsaObj,
	SecNssCoder &coder,				// for temp decoding
	Allocator &alloc)			// destination 
{
	memset(&cdsaObj, 0, sizeof(cdsaObj));
	PRErrorCode prtn;

	/* for caller's CE_GeneralName */
	CSSM_BOOL berEncoded = CSSM_FALSE;
	CE_GeneralNameType cdsaTag;
	
	/*
	 * At this point, depending on the decoded object's tag, we either
	 * have the final bytes to copy out, or we need to decode further.
	 * After this switch, if doCopy is true, give the caller a copy
	 * of nssObj.item.
	 */
	bool doCopy = true;
	switch(nssObj.tag) {
		case NGT_OtherName:		// ASN_ANY -> CE_OtherName
		{
			cdsaTag = GNT_OtherName;
			
			/* decode to coder memory */
			CE_OtherName *nssOther = 
				(CE_OtherName *)coder.malloc(sizeof(CE_OtherName));
			memset(nssOther, 0, sizeof(CE_OtherName));
			prtn = coder.decodeItem(nssObj.item, 
				kSecAsn1GenNameOtherNameTemplate, 
				nssOther);
			if(prtn) {
				clErrorLog("CL_nssGeneralNameToCssm: error decoding "
						"OtherName\n");
				CssmError::throwMe(CSSMERR_CL_UNKNOWN_FORMAT);
			}
			
			/* copy out to caller */
			clAllocData(alloc, cdsaObj.name, sizeof(CE_OtherName));
			clCopyOtherName(*nssOther, *((CE_OtherName *)cdsaObj.name.Data), 
				alloc);
			doCopy = false;
			break;
		}
		case NGT_RFC822Name:	// IA5String, done
			cdsaTag = GNT_RFC822Name;
			break;
		case NGT_DNSName:		// IA5String
			cdsaTag = GNT_DNSName;
			break;
		case NGT_X400Address:	// ASY_ANY, leave alone
			cdsaTag = GNT_X400Address;
			berEncoded = CSSM_TRUE;
			break;
		case NGT_DirectoryName:	// ASN_ANY --> NSS_Name
		{
			cdsaTag = GNT_DirectoryName;
			
			/* Decode to coder memory */
			NSS_Name *nssName = (NSS_Name *)coder.malloc(sizeof(NSS_Name));
			memset(nssName, 0, sizeof(NSS_Name));
			prtn = coder.decodeItem(nssObj.item, kSecAsn1NameTemplate, nssName);
			if(prtn) {
				clErrorLog("CL_nssGeneralNameToCssm: error decoding "
						"NSS_Name\n");
				CssmError::throwMe(CSSMERR_CL_UNKNOWN_FORMAT);
			}
			
			/* convert & copy out to caller */
			clAllocData(alloc, cdsaObj.name, sizeof(CSSM_X509_NAME));
			CL_nssNameToCssm(*nssName, 
				*((CSSM_X509_NAME *)cdsaObj.name.Data), alloc);
			doCopy = false;
			break;
		}
		case NGT_EdiPartyName:	// ASN_ANY, leave alone
			cdsaTag = GNT_EdiPartyName;
			berEncoded = CSSM_TRUE;
			break;
		case NGT_URI:			// IA5String
			cdsaTag = GNT_URI;
			break;
		case NGT_IPAddress:		// OCTET_STRING
			cdsaTag = GNT_IPAddress;
			break;
		case NGT_RegisteredID:	// OID
			cdsaTag = GNT_RegisteredID;
			break;
		default:
			clErrorLog("CL_nssGeneralNameToCssm: bad name tag\n");
			CssmError::throwMe(CSSMERR_CL_UNKNOWN_FORMAT);
	}	
	
	cdsaObj.nameType = cdsaTag;
	cdsaObj.berEncoded = berEncoded;
	if(doCopy) {
		clAllocCopyData(alloc, nssObj.item, cdsaObj.name);
	}
}