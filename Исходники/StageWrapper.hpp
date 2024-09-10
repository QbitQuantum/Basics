 static void initialize(std::shared_ptr<Stage> s, PointTableRef table)
 {
     s->l_initialize(table);
     s->initialize();
 }