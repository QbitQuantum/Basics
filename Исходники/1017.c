int fun(int *input, int *input_count, int len) {
	int dp[101][101], accu_count[101];
	int i, j, k, start, last;
	memset(accu_count, 0, sizeof(int) * 101);
	for(i = 0; i < 101; i++) {
		memset(dp[i], 0, sizeof(int) * 101);
	}
	accu_count[1] = input_count[1];
	for(i = 2; i <= len; i++)
		accu_count[i] = accu_count[i - 1] + input_count[i];

	for(k = 1; k <= K; k++) {
		start = last = 1;
		for(i = 1; i <= len; i++) {
			last = start;
			start = bSearch(input, start, i, input[i] - W);

			dp[i][k] = max(dp[i - 1][k], dp[start - 1][k - 1] + accu_count[i] - accu_count[start - 1]);
		}
	}
	return dp[len][K];
}