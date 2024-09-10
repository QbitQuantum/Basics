void compute() 
{
	for (int i=0; i<TUPLES; ++i) {
		verify[i] = 0;
	}

	q.threadInit();

#ifdef VERBOSE
	PrettyPrinterVisitor ppv;
	cout << "---------- QUERY PLAN START ----------" << endl;
	q.accept(&ppv);
	cout << "----------- QUERY PLAN END -----------" << endl;
#endif

	Operator::Page* out;
	Operator::GetNextResultT result; 
	
	if (q.scanStart() != Operator::Ready) {
		fail("Scan initialization failed.");
	}

	while(result.first == Operator::Ready) {
		result = q.getNext();

		out = result.second;

		Operator::Page::Iterator it = out->createIterator();
		void* tuple;
		while ( (tuple = it.next()) ) {
#ifdef VERBOSE2
			cout << q.getOutSchema().prettyprint(tuple, ' ') << endl;
#endif
			long long v = q.getOutSchema().asLong(tuple, 0);
			if (v <= 0 || v > TUPLES)
				fail("Values that never were generated appear in the output stream.");
			double d1 = q.getOutSchema().asDecimal(tuple, 1);
			double d2 = v + 0.1;
			if (d1 != d2)
				fail("Wrong tuple detected at join output.");
			verify[v-1]++;
		}
	}

	if (q.scanStop() != Operator::Ready) {
		fail("Scan stop failed.");
	}

#ifdef VERBOSE
	cout << "---------- QUERY PLAN START ----------" << endl;
	q.accept(&ppv);
	cout << "----------- QUERY PLAN END -----------" << endl;
#endif

	q.threadClose();
}