int main()
{
	int arr[] = { 4, 3, 1, 5, 7, 8, 9, 2 };	
	int n = 8;
	int key = 8;
	int res = *(int*)lsearch(&key, arr, n, sizeof(int), &IntCmp);
	printf("%d\n", res);		
	key = 6;
	void *res2 = lsearch(&key, arr, n, sizeof(int), &IntCmp);
	if (NULL == res2) 
		printf("True!");	
	return 0;
}