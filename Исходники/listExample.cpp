void listExample(){
	List<int> list;
	list.insert(1, list.end());
	list.insert(2, list.end());
	list.insert(3, list.end());

	int counter = 1;
	for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
		ASSERT_EQUALS(counter++, *it);
	}

	// C++11 syntactic sugar Range-based for-loop
	counter = 1;
	for (int& element : list) {
		ASSERT_EQUALS(counter++, element);
	}

	List<int>::Iterator it = list.begin();
	ASSERT_EQUALS(3, list.getSize());
	list.remove(++it);
	it = list.begin();
	ASSERT_EQUALS(*it, 1);
	list.insert(4, list.begin());
	list.insert(2, list.begin());


	// std::less<int> is a function object defined in <functional>
	// it simply calls operator< of the type compared
	list.sort(std::less<int>());
	it = list.begin();
	ASSERT_EQUALS(1, *it);

	it = list.find(EqualTo(3));
	ASSERT_EQUALS(3, *it);
	*it = 3;

	// The following insert should add to end of list
	list.insert(5);

	const List<int> list2(list);
	ASSERT_TRUE(list == list2);
	ASSERT_FALSE(list != list2);

	// ConstIterator example
	counter = 1;
	for (List<int>::ConstIterator cit = list2.begin();
	    cit != list2.end();
	    ++cit) {
		ASSERT_EQUALS(counter++, *cit);
	}
	List<int>::ConstIterator cit = list2.find(EqualTo(2));
	ASSERT_EQUALS(*cit, 2);

// Note: The the following line must not compile!
// *cit = 100;

}