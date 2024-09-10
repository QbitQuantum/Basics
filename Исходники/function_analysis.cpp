 void _doStore(const std::string& name) {
     if (_loads.count(name))
         return;
     _stores.insert(name);
 }