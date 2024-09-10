/* 
 * Search for line containing lineTitle, return portion of the line following ":".
 * Returns nonzero if no "lineTitle" line found.
 * Line must contain at least 3 tokens - lineTitle, ":", and the string we return. 
 */
static int fineLineWithTitle(TextParser &parser, 
	const char *lineTytle,
	char *str)			// caller allocates, RETURNED
{
	char lineBuf[LINE_LENGTH_MAX];
	parser.setCursor(0);
	if(!parser.findLine(lineTytle, lineBuf)) {
		return 1;
	}
	
	unsigned numTokens;
	const char **tokens;
	numTokens = parser.parseLine(lineBuf, tokens);
	if(numTokens < 3) {
		return 1;
	}
	
	/* copy all tokens after ":" to caller's string */
	str[0] = '\0';
	for(unsigned dex=2; dex<numTokens; dex++) {
		strcat(str, tokens[dex]);
		if(dex < (numTokens - 1)) {
			strcat(str, " ");
		}
	}
	
	/* Convenience: "Accelerate" is too big. */
	if(strstr(str, "Accelerate")) {
		strcpy(str, "vecLib");
	}
	/* so is CLMatrix */
	else if(strstr(str, "CLMatrix")) {
		strcpy(str, "CLM");
	}
	/* ditto MatrixFFT */
	else if(strstr(str, "MatrixFFT")) {
		strcpy(str, "Matrix");
	}
	return 0;
}