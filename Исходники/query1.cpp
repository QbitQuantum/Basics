void compute() 
{
	Operator::Page* out;
	Operator::GetNextResultT result; 
	
	startTimer(&timer);
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
			skata1 += *(unsigned long long*)tuple;
			skata2 += *((double*)tuple+1);
		}
	}

	if (q.scanStop() != Operator::Ready) {
		fail("Scan stop failed.");
	}
	stopTimer(&timer);
}