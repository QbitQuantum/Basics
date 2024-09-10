int main()
{
	int i, n, res, pos;
	while(scanf("%d", &n) != EOF)
	{
		for(i = 0;i < n;i++)
			scanf("%d", &arr[i]);

		res = 0;
		tailM[0] = arr[0];
		for(i = 1;i < n;i++)
		{
			if (tailM[res] < arr[i])
			{
				res++;
				tailM[res] = arr[i];
			}
			else
			{
				pos = Bsearch(arr[i], res);
				tailM[pos] = arr[i];
			}
		}
		printf("%d\n", res + 1);
	}
	return 0;
}