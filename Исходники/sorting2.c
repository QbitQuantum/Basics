void Qsort(long *Array, int lb, int ub){
	int pivot=0;
	if (lb>=ub){
		return;
	}
//	if((ub-lb) >10){
//		return;
//	}
	
	pivot = partition(Array, lb, ub);
	Qsort(Array, lb, pivot-1);
	Qsort(Array, pivot+1, ub);
}