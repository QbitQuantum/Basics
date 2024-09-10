  void test_remove() {
    List* lst = List::create(state);
    lst->append(state, one);
    lst->append(state, two);
    lst->append(state, one);
    lst->append(state, two);

    TS_ASSERT_EQUALS(lst->remove(state, one), (size_t)2);
    TS_ASSERT_EQUALS(lst->size(), (size_t)2);
    
    TS_ASSERT_EQUALS(lst->remove(state, two), (size_t)2);
    TS_ASSERT_EQUALS(lst->size(), (size_t)0);
  }