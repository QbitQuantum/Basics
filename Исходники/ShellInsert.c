void QSort( SqList* l, int low, int high )
{
	if( low >= high )
	{
		return;
	}
	int pivotloc = 0;
	pivotloc = Partition( l, low, high );
	QSort( l, low, pivotloc-1 );
	QSort( l, pivotloc+1, high );
}