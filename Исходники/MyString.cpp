int operator==(const char *S1, const MyString& S2) 
{
    if ((!S2.Data || !S2.Length()) && (!S1 || !strlen(S1))) {
		return 1;
	}
    if (!S2.Data || !S1) {
		return 0;
	}
    if (strcmp(S2.Data,S1)==0) {
		return 1;
	}
    return 0;
  }