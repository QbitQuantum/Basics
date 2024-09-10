void Qsort(vector<int> &list, int low, int high)
{
	int pivot = list[low]; // 设置pivot
	// 进行一次排序
	int low_tmp = low, high_tmp = high;
	while (low_tmp < high_tmp)
	{
		while (low_tmp < high_tmp && list[high_tmp] >= pivot)
			--high_tmp;
		// 小于pivot的数，换到左侧
		list[low_tmp] = list[high_tmp];
		while (low_tmp < high_tmp && list[low_tmp] <= pivot)
			++low_tmp;
		list[high_tmp] = list[low_tmp];
	}
	list[low_tmp] = pivot;
	// 完成一次排序
	Qsort(list, low, low_tmp-1); // 递归处理左子序列
	Qsort(list, low_tmp+1, high); // 递归处理左子序列
}