void KeyValuesTable::remove(const char * key) {
  QString ks = toUnicode(key);
  int index;
  
  for (index = 0; index != numRows(); index += 1) {
    if (text(index, 0) == ks) {
      delete_row(index);
      break;
    }
  }  
}