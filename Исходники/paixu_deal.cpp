void QSort(SqList&L,int low,int high){
//一趟对父序列分割为两个无序的子序列，对子序列递归调用自身,必须传进low和high
	//T(n)=O(nlogn),S(n)=O(logn),不稳定
	if(low<high){
		int mid=Partiotion(L,low,high);
		QSort(L,low,mid);
		QSort(L,mid,high);
	}

}