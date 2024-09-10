CHECK(~ConformationSet())
	delete cs;
RESULT

CHECK(readDCDFile())
		ConformationSet cs;
		cs.readDCDFile(BALL_TEST_DATA_PATH(ConformationSet_test.dcd));
		cs.resetScoring();
		TEST_EQUAL(cs.size(), 10)
RESULT

CHECK(writeDCDFile(const String& filename, const Size num = 0))
		ConformationSet cs;

		PDBFile pdb(BALL_TEST_DATA_PATH(ConformationSet_test.pdb));
		System sys;
		pdb.read(sys);
		cs.setup(sys);

		cs.readDCDFile(BALL_TEST_DATA_PATH(ConformationSet_test.dcd));
		cs.resetScoring();
		String tmp_filename;
		NEW_TMP_FILE(tmp_filename)

		cs.writeDCDFile(tmp_filename);
		TEST_FILE(tmp_filename.c_str(), BALL_TEST_DATA_PATH(ConformationSet_test.dcd))
RESULT

CHECK(setup())
	PDBFile pdb(BALL_TEST_DATA_PATH(ConformationSet_test.pdb));
	System sys;