void ClusterAStarTest::logStatsShouldRecordAllMetricsToStatsCollection()
{	
	HPAClusterAbstraction hpamap(new Map(acmap.c_str()), new HPAClusterFactory(), 
		new ClusterNodeFactory(), new EdgeFactory());
	hpamap.setClusterSize(TESTCLUSTERSIZE);

	hpamap.buildClusters();
	ClusterAStar castar;

	statCollection sc;
	p = castar.getPath(&hpamap, hpamap.getNodeFromMap(2,1), hpamap.getNodeFromMap(4,5));
	castar.logFinalStats(&sc);
	
	assert(p != 0);
	string catNE = "nodesExpanded";
	string catNT = "nodesTouched";
	string catPM = "peakMemory";
	string catST = "searchTime";
	
	statValue result;
	bool lookupResult = sc.lookupStat(catNE.c_str(), castar.getName() , result);
	CPPUNIT_ASSERT_MESSAGE("couldn't find nodesExpanded metric in statsCollection", lookupResult == true);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("nodesExpanded metric in statsCollection doesn't match expected result", (long)castar.getNodesExpanded(), result.lval);

	lookupResult = sc.lookupStat(catNT.c_str(), castar.getName() , result);
	CPPUNIT_ASSERT_MESSAGE("couldn't find nodesTouched metric in statsCollection", lookupResult == true);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("nodesTouched metric in statsCollection doesn't match expected result", (long)castar.getNodesTouched(), result.lval);

	lookupResult = sc.lookupStat(catPM.c_str(), castar.getName() , result);
	CPPUNIT_ASSERT_MESSAGE("couldn't find peakMemory metric in statsCollection", lookupResult == true);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("peakMemory metric in statsCollection doesn't match expected result", (long)castar.getPeakMemory(), result.lval);

	lookupResult = sc.lookupStat(catST.c_str(), castar.getName() , result);
	CPPUNIT_ASSERT_MESSAGE("couldn't find searchTime metric in statsCollection", lookupResult == true);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("searchTime metric in statsCollection doesn't match expected result", (double)castar.getSearchTime(), result.fval);

}