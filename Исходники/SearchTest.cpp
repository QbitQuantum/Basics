void TestIterativeValue(int depth) {
	// setup book and cache
	CCache acache(2);
	cache = &acache;
	const int nEmpty = 22;
	CBook* oldBook = book;
	book = NULL;
	InitializeCache();
	SetBookHeights(nEmpty);
	mpcs = CMPCStats::GetMPCStats('J','A',5);

	// testing
	const COsGame osGame = LoadTestGames().at(0);
	const CQPosition testPosition = PositionFromEmpties(osGame, nEmpty);
	std::vector<CMoveValue> mvs = createMoves(testPosition);
	Pos2 pos2;
	pos2.Initialize(testPosition.BitBoard(), testPosition.BlackMove());
	u4 nValued=0;
	std::vector<CMoveValue> mvsEvaluated;
	ValueMulti(pos2, depth, -kInfinity, kInfinity, 4, 1, mvs, false, false, mvsEvaluated, nValued);
//	cout << " nValued = " << nValued << "\n";
//	cout << " mvsEvaluated = \n";
//	for (int i=0; i<mvsEvaluated.size(); i++) {
//		CMoveValue mv = mvsEvaluated.at(i);
//		cout << "new CMoveValue(" << mv.move << "," << mv.value << "),\n";
//	}
//	cout << "\n";

	// tear down book and cache
	book = oldBook;
	cache = NULL;
}