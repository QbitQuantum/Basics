void GMSourceView::saveSettings(const FXString & key) const {
  getApp()->reg().writeBoolEntry(key.text(),"source-list-sort-reverse",sourcelist->getSortFunc()==source_list_sort_reverse);
  getApp()->reg().writeBoolEntry(key.text(),"source-list",getParent()->shown());
  }