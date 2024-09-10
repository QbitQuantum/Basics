int main()
{
	int i, len, res, pos, ncase = 1;
	while(scanf("%d", &arr[0]), arr[0] != -1)
	{
		for(i = 1;arr[i-1] != -1;i++)
			scanf("%d", &arr[i]);

		len = i -1 ;
		res = 0;
		tailM[0] = arr[0];
		for(i = 1;i < len;i++)
		{
			if (tailM[res] > arr[i])
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
		printf("Test #%d:\n  maximum possible interceptions: %d\n\n", ncase++, res + 1);
	}
	return 0;
}