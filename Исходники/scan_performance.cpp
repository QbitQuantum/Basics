  void BenchmarkSetUp() {
    _tablescanNormal = std::make_shared<TableScan>(make_unique<EqualsExpression<hyrise_int_t>>(0, 0, _value));
    _tablescanNormal->setEvent("NO_PAPI");
    _tablescanNormal->addInput(_table);

    _tablescanSpecial = std::make_shared<TableScan>(make_unique<ExampleExpression>(0, _value));
    _tablescanSpecial->setEvent("NO_PAPI");
    _tablescanSpecial->addInput(_table);
  }