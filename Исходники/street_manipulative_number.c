int maxk(int A[], int N) {
	int i, k, ind, mask, prefix;
	int bits[102], freq[102], len;
	
	mask = 0;
	len = 0;
	for (k = 31; k >= 0; k--) {
		len = 0;
		memset(bits, 0, sizeof(bits[0])*N);
		memset(freq, 0, sizeof(freq[0])*N);
		mask = mask | (1<<k);
		for (i = 0; i < N; i++) {
			prefix = A[i] & mask;
			// for this problem linear search is fine
			ind = lfind(prefix, bits, len);
			if (ind == -1) {
				bits[len] = prefix;
				freq[len]++;
				len++;
			}
			else {
				freq[ind]++;
			}
		}
		// second pass: find the sequence of bits whose frequency exceeds 50%
		for (i = 0; i < N; i++) {
			prefix = A[i] & mask;
			ind = lfind(prefix, bits, len);
			if (freq[ind] > N/2)
				break;
		}
		if (i == N)
			return k;
	}
	
	return -1;
}