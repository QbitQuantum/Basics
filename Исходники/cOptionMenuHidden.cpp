void cOptionMenuHidden::addSubmenu(const char *name, const char *parent) {
  COptionMenu *tmenu = new COptionMenu(size, listener, tag);
  
  if(parent == NULL) {
    addEntry(tmenu, (char*)name);
  }
  else {
    getSubMenu(findSubmenu(parent))->addEntry(tmenu, (char*)name);
  }
  
  char *tname = new char[MAX_MENU_NAME];
  strncpy(tname, name, MAX_MENU_NAME);
  m_submenu_names.push_back(tname);
  ++m_submenu_items;
}