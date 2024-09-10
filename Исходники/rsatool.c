static int rt_digest(opParams *op)
{
	int 		irtn;
	CSSM_DATA	ptext;
	CSSM_DATA	digest = {0, NULL};
	CSSM_RETURN	crtn;
	unsigned	len;
	
	if((op->plainFileName == NULL) || (op->sigFileName == NULL)) {
		printf("***Need plainFileName and sigFileName to digest.\n");
		return 1;
	}
	irtn = readFile(op->plainFileName, &ptext.Data, &len);
	if(irtn) {
		printf("***Error reading %s\n", op->plainFileName);
		return irtn;
	}
	ptext.Length = len;
	crtn = cspDigest(op->cspHand,
		op->alg,
		CSSM_FALSE,		// mallocDigest - let CSP do it
		&ptext,
		&digest);
	if(crtn) {
		printError("cspDigest", crtn);
		return 1;
	}
	irtn = writeFile(op->sigFileName, digest.Data, digest.Length);
	if(irtn) {
		printf("***Error writing %s\n", op->sigFileName);
	}
	else if(!op->quiet){
		printf("...wrote %lu bytes to %s\n", digest.Length, op->sigFileName);
	}
	free(ptext.Data);						// allocd by readFile
	appFreeCssmData(&digest, CSSM_FALSE);	// by CSP
	return irtn;
}