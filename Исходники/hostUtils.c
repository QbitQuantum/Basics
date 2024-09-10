void sortIndicesHost (int * cardinalities, int * indices, int size){
	int i;
	for(i=0;i<size;i++) indices[i] = i;
	keys = cardinalities;
	qsort(indices,size,sizeof(int),compare);
}