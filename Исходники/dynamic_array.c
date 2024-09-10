//void QSort
void QSort(DArray *L, pDArrayCmp cmp, int left, int right)
{
	void *key,*tmp;
	int i = left,j = right;
	key= L->data[left];

	while(i < j)
	{
		while((cmp(key,L->data[j]) <= 1) && (i<j))
		{
			--j;
		}
		L->data[i] = L->data[j];
		
		while((1 <= cmp(key, L->data[i])) && (i<j))
		{
			++i	;
		}

		L->data[j] = L->data[i];
	}
	L->data[i] = key;
	printf("***the middle index is %d\n",i);
	DArrayForeach(L,pDArrayVisit_PrintInt, NULL);
	
	if((i-1) > left)  QSort(L,cmp, left, i-1);
	if(right > (i+1)) QSort(L,cmp, i+1, right);
}