char*
UnsignedIntToCharPointer(unsigned int x) {
	unsigned int n = Log10(x) + 1;
	char* nArray = (char*)calloc(n + 1, sizeof(char));

	for(unsigned int i = 0; i < n; ++i, n /= 10) {
		nArray[i] = (x % 10) + '0';
	}

	return(nArray);
}