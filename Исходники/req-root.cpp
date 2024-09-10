template<class T> void root<T>::scan(type_scan::Scanner& scanner) const {
  scanner.scan(*static_cast<const T*>(this));
}