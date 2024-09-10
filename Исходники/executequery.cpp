void compute() 
{
	unsigned long long cycles = 0;
	Operator::GetNextResultT result; 
	result.first = Operator::Ready;
	
	startTimer(&cycles);

	if (q.scanStart() == Operator::Error)
		fail("Scan initialization failed.");

	while(result.first == Operator::Ready) {
		result = q.getNext();

		if (result.first == Operator::Error)
			fail("GetNext returned error.");

		Operator::Page::Iterator it = result.second->createIterator();
		void* tuple;
		while ((tuple = it.next()) ) {
			cout << q.getOutSchema().prettyprint(tuple, '|') << endl;
		}
	}

	if (q.scanStop() == Operator::Error) 
		fail("Scan stop failed.");

	stopTimer(&cycles);

#warning Cycles to seconds conversion is hardcoded for our prototype system
	cout << "ResponseTimeInSec: " << cycles/1000./1000./2000. << endl;
}