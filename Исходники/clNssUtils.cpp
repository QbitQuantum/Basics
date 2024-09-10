void CL_cssmAuthorityKeyIdToNss(
	const CE_AuthorityKeyID 	&cdsaObj,
	NSS_AuthorityKeyId 			&nssObj,
	SecNssCoder 				&coder) 
{
	memset(&nssObj, 0, sizeof(nssObj));
	if(cdsaObj.keyIdentifierPresent) {
		nssObj.keyIdentifier = (CSSM_DATA_PTR)coder.malloc(sizeof(CSSM_DATA));
		coder.allocCopyItem(cdsaObj.keyIdentifier, *nssObj.keyIdentifier);
	}
	if(cdsaObj.generalNamesPresent ) {
		/* GeneralNames, the hard one */
		CL_cssmGeneralNamesToNss(*cdsaObj.generalNames,
			nssObj.genNames, coder);
	}
	if(cdsaObj.serialNumberPresent) {
		coder.allocCopyItem(cdsaObj.serialNumber,nssObj.serialNumber);
	}
}