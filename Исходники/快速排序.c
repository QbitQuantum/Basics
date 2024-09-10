void QSort(int a[],int low,int high)
{
	int key;
	if(low<high)
	{
		key=partition(a,low,high);
		QSort(a,low,key-1);
		QSort(a,key+1,high);
	}
}