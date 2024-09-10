void compute() 
{
	q.threadInit();

	Operator::Page* out;
	Operator::GetNextResultT result; 
	
	if (q.scanStart() != Operator::Ready) {
		fail("Scan initialization failed.");
	}

	while(result.first == Operator::Ready) 
	{
		result = q.getNext();

		out = result.second;

		Operator::Page::Iterator it = out->createIterator();
		void* tuple;
		while ( (tuple = it.next()) ) 
		{
#ifdef VERBOSE2
			cout << q.getOutSchema().prettyprint(tuple, ' ') << endl;
#endif

			DataT d;
			d.v1 = q.getOutSchema().asLong(tuple, 0);
			d.v2 = q.getOutSchema().asLong(tuple, 1);
			d.v3 = q.getOutSchema().asInt(tuple, 2);
			finalresult.push_back(d);
		}
	}

	if (q.scanStop() != Operator::Ready) {
		fail("Scan stop failed.");
	}

	q.threadClose();
}