int main()
{
	int len=7;
	//scanf_s("%d", &len);
	int p[8] = { 6, 12, 4, 63, 2, 35, 11 };
	InsertionSort insert;
	insert.insertionSort(p, len);
	//insert_sort(p, len);
	for (int i = 0; i < len; i++)
	{
		printf("%d,", *(p + i));
	}
	scanf_s("%d", &len);
    return 0;
}