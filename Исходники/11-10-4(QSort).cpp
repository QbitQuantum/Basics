int main()
 {
	int data[MaxN];
	int scale;
	InputData(data,&scale);
	QSort(data,0,scale-1);
	OutputData(data,scale);
	return 0;
}