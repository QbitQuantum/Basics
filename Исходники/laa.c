Associate* makeLAA(int arraySize,int patternSize){
	Associate *result=Calloc(Associate,1);
	result->keys=Calloc(int,arraySize*patternSize);
	result->patternSize=patternSize;
	result->array=Calloc(void*,arraySize);
	return result;
}