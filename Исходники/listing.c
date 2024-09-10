  void
readIndexFileLine(statementKindType *statementKindPtr, int *indexAddressPtr, int *indexLineNumberPtr)
{
	statementKindType	 statementKindRead;
	int			 indexAddressRead;
	int			 indexLineNumberRead;

	statementKindRead = (statementKindType) getw(indexFileForPass2);
	indexAddressRead = getw(indexFileForPass2);
	indexLineNumberRead = getw(indexFileForPass2) - 1;
	if (!feof(indexFileForPass2)) {
		*statementKindPtr = statementKindRead;
		*indexAddressPtr = indexAddressRead;
		*indexLineNumberPtr = indexLineNumberRead;
	} else {
		*indexLineNumberPtr += 1;
	}
}