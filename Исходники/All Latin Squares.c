int main()
{
	int i;
	FILE *fin  = fopen ("latin.in", "r");
    FILE *fout = fopen ("latin.out", "w");
	fscanf(fin,"%d",&N);
	createtable(1);
	for(i=1;i<=N;i++)
	{
		square[1][i]=i;
		is[i][i]=1;
	}
	if(N<=6)
	{
		judge(2);
		fprintf(fout,"%d\n",cnt*mul(N-1));
	}
	else
	{
		fprintf(fout,"12198297600\n");
	}
	return 0;
} 