void ConcentrateInit(int k){

	double **dm = malloc(sizeof(double*)* GetDataSize());	
	int i;
	for (i = 0; i < GetDataSize(); ++i)
		dm[i] = malloc(sizeof(double)* GetDataSize());
	int j;
	for (i = 0; i < GetDataSize(); ++i)
		for (j = i; j < GetDataSize(); ++j){
			value v1, v2;
			GetIthData(i, &v1);
			GetIthData(j, &v2);
			dm[i][j] = data.distance(&v1, &v2);
			dm[j][i] = dm[i][j];
		}
	double *v = malloc(sizeof(double)* GetDataSize());
	int *vPos = malloc(sizeof(int)* GetDataSize());

	double *lineSum = malloc(sizeof(double)* GetDataSize());
	for (i = 0; i < GetDataSize(); ++i){
		lineSum[i] = 0;
		for (j = 0; j < GetDataSize(); ++j)
			lineSum[i] += dm[i][j];
	}
	for (i = 0; i < GetDataSize(); ++i)
		vPos[i]=i;
	for (i = 0; i < GetDataSize(); ++i)
		v[i] = CalculateV(dm, lineSum, i);
	QuickSortDouble(v,vPos,GetDataSize());
	QuickSortInt(vPos,k);
	for (i = k-1; i >= 0; --i)
		AddCentroid(vPos[i]);
	for (i = 0; i < GetDataSize(); ++i)
	{
		free(dm[i]);
	}
	free(dm);
	free(v);
	free(vPos);
	free(lineSum);
}