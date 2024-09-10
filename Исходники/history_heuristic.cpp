void HistoryHeuristic::QSort(ChessMove *source, int low, int high)
{
	int i;
	if (low < high)
	{
		i = Partition(source, low, high);
		QSort(source, low, i - 1);
		QSort(source, i+1, high);
	}
}