QoreHashNode* ParseOptionMaps::getCodeToStringMap() const {
   QoreHashNode* h = new QoreHashNode;
   
   QoreString key;
   for (pomap_t::const_iterator i = pomap.begin(), e = pomap.end(); i != e; ++i) {
      key.clear();
      key.sprintf(QLLD, i->first);
      h->setKeyValue(key.c_str(), new QoreStringNode(i->second), 0);
   }
   
   return h;
}