 ~KeepAliveRegistrar() {
   for (int i = _keep_alive.length() - 1; i >= 0; --i) {
     ConstantPool* cp = _keep_alive.at(i);
     int idx = _thread->metadata_handles()->find_from_end(cp);
     assert(idx > 0, "Must be in the list");
     _thread->metadata_handles()->remove_at(idx);
   }
 }