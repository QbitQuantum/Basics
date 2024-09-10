  ~nmethodCollector() {
    if (_nmethods != NULL) {
      for (int i=0; i<_nmethods->length(); i++) {
	nmethodDesc* blob = _nmethods->at(i);
	if (blob->map()!= NULL) {
	  FREE_C_HEAP_ARRAY(jvmtiAddrLocationMap, blob->map());
	}
      }
      delete _nmethods;
    }
  }