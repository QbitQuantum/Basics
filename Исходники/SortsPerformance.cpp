double sortTime(int method, int numSize, int repeat)
{
	Rand r;
	Timer t;
	double res = 0.0;
	for (int j = 0; j < repeat; j++)
	{
		auto vec = r.getRandIntVec(numSize);
		t.startTime();
		if (method == 0) MergeSort::sort(vec);
		else if (method == 1) InsertionSort::sort(vec);
		else if (method == 2) HybridSort::sort(vec);
		else if (method == 3) MergeBU::sort(vec);
		t.endTime();
		res += t.elapsedSeconds();

		assert(isSorted(vec));
	}
	return res / repeat;
}