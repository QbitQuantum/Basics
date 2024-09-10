/**
 * returned function length can be somewhat different, more than real, due to other function code
 * not described in export table (for example: IsDebuggerPresent real length is 19, but
 * this function will return 173)
 */
int _scitGetExportedFunctionCodeLength(LPCSTR lpApiName, ScitApiDescriptor_t *aFunctions, DWORD nFunctions) {
	DWORD i;


	if (!lpApiName || !aFunctions || nFunctions <= 0) {
		return 0;
	}

	/* todo: fixme: implement better method to get code length */
	for (i = 0; i < nFunctions; i++) {
		/* first - find function entry in sorted array */
		if (!lstrcmpA(aFunctions[i].lpName, lpApiName)) {
			/* get next entry */
			i++;
			if (i < nFunctions) {
				/* calculate function code length by next function */
				return (DWORD)aFunctions[i].fAddr - (DWORD)aFunctions[i - 1].fAddr;
			}

			break;
		}
	}

	return 0;
}