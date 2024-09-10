void QSort(int *pint, int Low_Index, int High_Index)
{
	if (Low_Index < High_Index)
	{
		//选一个pv值，把数据分别放在pv值得左右两边，并把pivot位置返回出来。。
		int pivot = Partition(pint, Low_Index, High_Index);

		//对子序列1排序
		QSort(pint, Low_Index, pivot - 1);
		//对子序列2排序
		QSort(pint, pivot + 1, High_Index);
	}
}