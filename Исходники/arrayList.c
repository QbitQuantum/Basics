void QSort(SqList *L, int low, int high)
{
	// 对顺序表L中的子序列L->elem[low...high]做快速排序
	if(low < high){
		int pivotloc = Partition(L, low, high);	// 一分为二
		QSort(L, low, pivotloc-1);
		QSort(L, pivotloc+1, high);
	}
}