int main()
{
	int n;
	scanf("%d", &n);
	int dp[2][3];
	dp[0][0] = 1;
	dp[0][1] = 0;
	dp[0][2] = 0;
	int cur = 0;
	for (int i = 0; i < n; ++i)
	{
		cur = 1 - cur;
		char c = getC();
		if (c == '0')
		{
			dp[cur][0] = dp[1 - cur][1] + dp[1 - cur][0];
			dp[cur][1] = dp[1 - cur][1] + dp[1 - cur][2];
			dp[cur][2] = 0;
		}
		else if (c == '1')
		{
			dp[cur][0] = 0;
			dp[cur][1] = dp[1 - cur][0] + dp[1 - cur][1];
			dp[cur][2] = dp[1 - cur][1] + dp[1 - cur][2];
		}
		else
		{
			dp[cur][0] = 0;
			dp[cur][1] = dp[1 - cur][0] + dp[1 - cur][1];
			dp[cur][2] = 0;
		}
		dp[cur][0] %= mod;
		dp[cur][1] %= mod;
		dp[cur][2] %= mod;
	}
	printf("%d\n", dp[cur][0] + dp[cur][1]);
	return 0;
}