void LinkedHashMapTest::testKeySet() {

    LinkedHashMap<int, std::string> hashMap;
    populateMap(hashMap);
    Set<int>& set = hashMap.keySet();
    CPPUNIT_ASSERT_MESSAGE("Returned set of incorrect size()", set.size() == hashMap.size());
    for (int i = 0; i < MAP_SIZE; i++) {
        CPPUNIT_ASSERT_MESSAGE("Returned set does not contain all keys", set.contains(i));
    }

    {
        LinkedHashMap<int, std::string> localMap;
        localMap.put(0, "test");
        Set<int>& intSet = localMap.keySet();
        CPPUNIT_ASSERT_MESSAGE("Failed with zero key", intSet.contains(0));
    }
    {
        LinkedHashMap<int, std::string> localMap;
        localMap.put(1, "1");
        localMap.put(102, "102");
        localMap.put(203, "203");

        Set<int>& intSet = localMap.keySet();
        Pointer< Iterator<int> > it(intSet.iterator());
        int remove1 = it->next();
        it->hasNext();
        it->remove();
        int remove2 = it->next();
        it->remove();

        ArrayList<int> list;
        list.add(1);
        list.add(102);
        list.add(203);

        list.remove(remove1);
        list.remove(remove2);

        CPPUNIT_ASSERT_MESSAGE("Wrong result", it->next() == list.get(0));
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong size", 1, localMap.size());
        it.reset(intSet.iterator());
        CPPUNIT_ASSERT_MESSAGE("Wrong contents", it->next() == list.get(0));
    }
    {
        LinkedHashMap<int, std::string> map2(101);
        map2.put(1, "1");
        map2.put(4, "4");

        Set<int>& intSet = map2.keySet();
        Pointer< Iterator<int> > it2(intSet.iterator());

        int remove3 = it2->next();
        int next;

        if (remove3 == 1) {
            next = 4;
        } else {
            next = 1;
        }
        it2->hasNext();
        it2->remove();
        CPPUNIT_ASSERT_MESSAGE("Wrong result 2", it2->next() == next);
        CPPUNIT_ASSERT_EQUAL_MESSAGE("Wrong size 2", 1, map2.size());
        it2.reset(intSet.iterator());
        CPPUNIT_ASSERT_MESSAGE("Wrong contents 2", it2->next() == next);
    }
}