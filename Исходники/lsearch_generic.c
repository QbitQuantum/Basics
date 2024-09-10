int main(int argc, char const *argv[])
{
	int size = 5;
	int number = 3;

	// lsearch 线性查找
	int larr[] = {6, 4, 7, 3, 10};
	int *found = (int *)lsearch(&number, larr, 5, sizeof(int), intCmp);

	printf("%d\n", *found);

	// bsearch 二分查找
	int barr[] = {3, 4, 6, 7, 10};
	found = (int *)lsearch(&number, barr, 5, sizeof(int), intCmp);

	printf("%d\n", *found);

	return 0;
}