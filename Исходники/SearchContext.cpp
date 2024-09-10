SearchContext::SearchContext(const Point* points_begin, const Point* points_end)
	: mTree(nullptr)
	, mKDTreeMemPool(nullptr)
	, mIteratorMemPool(nullptr)
{
#ifdef _ENABLE_STATS_LOGGING
	spxCurrentContext = this;
#endif // _ENABLE_STATS_LOGGING

	int64_t pointCount = points_end - points_begin;

	{
		// Add and sort all points on rank
		mPoints.assign(points_begin, points_end);

		std::sort(mPoints.begin(), mPoints.end(),
			[] (const Point& inLHS, const Point& inRHS)
		{
			return inLHS.rank < inRHS.rank;
		});
	}

	{
		// Create KDTree Mem Pool
		int minimumNodeCount	= (int) (pointCount / kBinSize) + 1;
		int byteCount			= sizeof(KdTree<Axis_X>) * minimumNodeCount;
		mKDTreeMemPool			= new MemoryPool(byteCount);
	}

	{
		// Create iterator mem pool
		// DANGEROUS: Can overrun memory here,
		// but it's marginally faster than using a checked mem pool...
		static const int kIteratorMemPoolMaxCount = 2000;
		mIteratorMemPool = (SearchIterator*) _aligned_malloc(sizeof(SearchIterator)*kIteratorMemPoolMaxCount, __alignof(SearchIterator));
	}

	{
		// Create KDTree
		mTree = mKDTreeMemPool->Alloc< KdTree<Axis_X> >();
		INC_KDTREE_COUNT;

#ifdef _BALANCE_KDTREE
		std::vector<CoordPairAndRank> coords;
		coords.reserve(mPoints.size());

		for (auto& p : mPoints)
		{
			coords.emplace_back( p );
		}

		mTree->Fill(*mKDTreeMemPool, coords);
#else
		for (auto& p : mPoints)
		{
			mTree->Add(*mKDTreeMemPool, p);
		}
#endif // _BALANCE_KDTREE

		mTree->Finalise();
	}

#ifdef _PRINT_POINTS_AND_QUERIES
	if (pointCount > 1) // Avoid robustness test.
	{
		DataPrinter::DeleteFiles();
		DataPrinter::PrintPoints(&(*mPoints.begin()), &(*mPoints.end()));

		auto copyPoints = mPoints;
		std::sort(copyPoints.begin(), copyPoints.end(),
			[] (const Point& inLHS, const Point& inRHS)
		{
			return inLHS.x < inRHS.x;
		});

		DataPrinter::PrintPoints(&(*copyPoints.begin()), &(*copyPoints.end()), "InputSortedOnX.txt");

		std::sort(copyPoints.begin(), copyPoints.end(),
			[] (const Point& inLHS, const Point& inRHS)
		{
			return inLHS.y < inRHS.y;
		});

		DataPrinter::PrintPoints(&(*copyPoints.begin()), &(*copyPoints.end()), "InputSortedOnY.txt");
	}
#endif // _PRINT_POINTS_AND_QUERIES
}