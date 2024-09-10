	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int blockHeights[]        = {4,7};
			int expected__            = 11;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int blockHeights[]        = {7,4};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int blockHeights[]        = {7};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int blockHeights[]        = {4};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int blockHeights[]        = {48,1,50,1,50,1,48};
			int expected__            = 196;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int blockHeights[]        = {49,2,49,2,49};
			int expected__            = 147;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int blockHeights[]        = {44,3,44,3,44,47,2,47,2,47,2};
			int expected__            = 273;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 7: {
          int blockHeights[]        = {2, 1, 1, 33, 40};
			int expected__            = 42;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 8: {
          int blockHeights[]        = {11, 6, 6, 6};
			int expected__            = 18;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 9: {
			int blockHeights[]        = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = BlockTower().getTallest(vector <int>(blockHeights, blockHeights + (sizeof blockHeights / sizeof blockHeights[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}