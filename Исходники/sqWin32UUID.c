int
MakeUUID(char *location) {
	if (CoCreateGuid((GUID*)location) == S_OK)
		return 1;
	FAIL();
	return 0;
}