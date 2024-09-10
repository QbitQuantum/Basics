int WinShortToLongPath(char *shortPath, char* longPath, int maxPath) {
	int result = GetLongPathNameA(shortPath, longPath, maxPath);  // use ANSI version
	if ((result >= maxPath) || (result == 0)) return -1;  // failed
	return 0;
}