/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
	int i = itoa_s(n, s, 0);
	s[i] = '\0';
}