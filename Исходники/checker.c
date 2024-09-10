int main()
{
	int i, j;

	freopen("checker.in", "r", stdin);
	freopen("checker.out", "w", stdout);

	scanf("%d", &n);
	n1 = n - 1;

	for (nsol = 0, i = 0; i < 256; i++)
		acol[i] = adiag1[i] = adiag2[i] = 0;

	if (n >= 8) {
		for (i = 0; i < (n / 2); i++) {
			PUT(0, i);
			search(1);
			REMOVE(0, i);
		}

		nsol *= 2;

		if ((n % 2) == 1) {
			PUT(0, (n / 2));
			search(1);
		}
	} else {
		search(0);
	}

	for (i = 0; i < 3; i++) {
		for (j = 0; j < n; j++)
			printf(((j + 1) < n) ? "%d " : "%d\n", sol[i][j] + 1);
	}

	printf("%d\n", nsol);

	return 0;
}