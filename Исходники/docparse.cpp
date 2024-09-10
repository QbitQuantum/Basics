  JsonObject *analyze(ParseTree *tree) {
    functions_ = new (pool_) JsonList();
    methodmaps_ = new (pool_) JsonList();
    enums_ = new (pool_) JsonList();
    constants_ = new (pool_) JsonList();
    typesets_ = new (pool_) JsonList();
    typedefs_ = new (pool_) JsonList();

    for (size_t i = 0; i < tree->statements()->length(); i++) {
      Statement *stmt = tree->statements()->at(i);
      stmt->accept(this);
    }

    JsonObject *obj = new (pool_) JsonObject();
    obj->add(cc_.add("functions"), functions_);
    obj->add(cc_.add("methodmaps"), methodmaps_);
    obj->add(cc_.add("enums"), enums_);
    obj->add(cc_.add("constants"), constants_);
    obj->add(cc_.add("typesets"), typesets_);
    obj->add(cc_.add("typedefs"), typedefs_);
    return obj;
  }