  void BenchmarkSetUp() {
    sm = StorageManager::getInstance();

    t = sm->getTable("order_line");

    gs = std::make_shared<GroupByScan>();
    gs->setEvent("NO_PAPI");
    gs->addInput(t);

    sum = new SumAggregateFun(t->numberOfColumn("OL_AMOUNT"));

    gs->addFunction(sum);
  }