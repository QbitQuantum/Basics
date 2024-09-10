  void test_send_then_receive() {
    GCTokenImpl gct;
    chan->send(state, gct, Qtrue);

    TS_ASSERT(kind_of<List>(chan->value()));
    List* lst = as<List>(chan->value());
    TS_ASSERT_EQUALS(lst->size(), 1U);
    TS_ASSERT_EQUALS(lst->locate(state, 0), Qtrue);

    CallFrame cf;
    Object* obj = chan->receive(state, gct, &cf);
    TS_ASSERT_EQUALS(obj, Qtrue);
    TS_ASSERT_EQUALS(lst->size(), 0U);
  }