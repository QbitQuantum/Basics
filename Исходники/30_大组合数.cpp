ll Comb(int n, int m, int k) {
	set(dp, 0); v.clear(); int tmp = k;
	for (int i = 2; i * i <= tmp; i++) {
		if (tmp % i == 0) {
			int num = 0;
			while (tmp % i == 0) {
				tmp /= i;
				num++;
			}
			v.pb(i);
		}
	} if (tmp != 1) v.pb(tmp);
	ll ans = Cal(n - m + 1, n, k, 1);
	for (int j = 0; j < v.size(); j++) {
		ans = ans * Pow(v[j], dp[j], k) % k;
	}
	ans = ans * inv(Cal(2, m, k, -1), k) % k;
	return ans;
}