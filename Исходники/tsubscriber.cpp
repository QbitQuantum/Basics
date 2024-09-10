static void test_memfunc(void) {
	test_caseStart("Testing member functions");

	{
		Test test;
		const Test ctest;
		Sender<int> s;
		tuple<int> x(2);
		s.subscribe(mem_recv(&test,&Test::test_func6));
		s.subscribe(bind1_mem_recv(2,&test,&Test::test_func7));
		s.subscribe(bind1_mem_recv(x,&test,&Test::test_func8));
		s.subscribe(bind1_mem_recv(const_cast<const tuple<int>&>(x),&test,&Test::test_func9));
		s.subscribe(bind1_mem_recv(x,&ctest,&Test::test_func10));
		s.subscribe(bind1_mem_recv(const_cast<const tuple<int>&>(x),&ctest,&Test::test_func11));
		s.send(1);
		for(size_t i = 6; i <= 11; ++i)
			test_assertSize(calls[i],1);
	}

	{
		Test test;
		const Test ctest;
		Sender<int&> s;
		tuple<int> x(2);
		s.subscribe(mem_recv(&test,&Test::test_func12));
		s.subscribe(bind1_mem_recv(x,&test,&Test::test_func13));
		s.subscribe(bind1_mem_recv(x,&ctest,&Test::test_func14));
		int y = 1;
		s.send(y);
		for(size_t i = 12; i <= 14; ++i)
			test_assertSize(calls[i],1);
	}

	test_caseSucceeded();
}