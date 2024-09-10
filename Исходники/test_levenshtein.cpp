void LevenshteinTest::TestGAS()
{
	StdBenchmark* bench = new StdBenchmark();
	Levenshtein* laligner = new Levenshtein();
	
	// hyp: a b c
	// ref: a * c
	Properties::SetProperties(bench->GetProperties(2));
	laligner->SetSegments(bench->GetTest(2), NULL, false);
	laligner->Align();
	GraphAlignedSegment* res = laligner->GetResults();
	cout << "Testing single insertion... ";
	cout.flush();
	assert(res->GetNonNullReference(1) == NULL);
	assert(res->GetPreviousNonNullReference(1)->GetText() == "a");
	assert(res->GetPreviousNonNullReference(0) == NULL);
	assert(res->GetNextNonNullReference(1)->GetText() == "c");
	assert(res->GetNextNonNullReference(2) == NULL);
	assert(res->GetNextNonNullReference(6) == NULL);
	cout << "OK." << endl;
	
	// hyp: a b c
	// ref: * * *
	Properties::SetProperties(bench->GetProperties(4));
	laligner->SetSegments(bench->GetTest(4), NULL, false);
	laligner->Align();
	res = laligner->GetResults();
	cout << "Testing insertions only... ";
	assert(res->GetNextNonNullReference(1) == NULL);
	assert(res->GetPreviousNonNullReference(1) == NULL);
	assert(res->GetNextNonNullReference(1) == NULL);
	cout << "OK." << endl;
	
	// hyp: a b c
	// ref: a * c
	Properties::SetProperties(bench->GetProperties(2));
	laligner->SetSegments(bench->GetTest(2), NULL, true);
	laligner->Align();
	res = laligner->GetResults();
	cout << "Testing single insertion Compressed... ";
	cout.flush();
	assert(res->GetNonNullReference(1) == NULL);
	assert(res->GetPreviousNonNullReference(1)->GetText() == "a");
	assert(res->GetPreviousNonNullReference(0) == NULL);
	assert(res->GetNextNonNullReference(1)->GetText() == "c");
	assert(res->GetNextNonNullReference(2) == NULL);
	assert(res->GetNextNonNullReference(6) == NULL);
	cout << "OK." << endl;
	
	// hyp: a b c
	// ref: * * *
	Properties::SetProperties(bench->GetProperties(4));
	laligner->SetSegments(bench->GetTest(4), NULL, true);
	laligner->Align();
	res = laligner->GetResults();
	cout << "Testing insertions only Compressed... ";
	cout.flush();
	assert(res->GetNextNonNullReference(1) == NULL);
	assert(res->GetPreviousNonNullReference(1) == NULL);
	assert(res->GetNextNonNullReference(1) == NULL);
	cout << "OK." << endl;
}