void compute() 
{
	for (int i=0; i<TUPLES*TUPLES; ++i) {
		verify[i] = 0;
	}

	q.threadInit();

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
#ifdef VERBOSE
			cout << q.getOutSchema().prettyprint(tuple, ' ') << endl;
#endif
			long long v = q.getOutSchema().asLong(tuple, 0);
			if (v <= 0 || v > TUPLES)
				fail("Values that never were generated appear in the output stream.");
			double d1 = q.getOutSchema().asDecimal(tuple, 1);
			int i2 = (int) lrint(d1);
			int idx = (v-1)*TUPLES + (i2-1);
			if (idx < 0 || idx >= TUPLES*TUPLES)
				fail("Wrong values appear in output.");
			verify[idx]++;
		}
	}

	if (q.scanStop() != Operator::Ready) {
		fail("Scan stop failed.");
	}

	q.threadClose();
}