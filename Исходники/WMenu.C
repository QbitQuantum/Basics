WMenuItem *WMenu::addMenu(const std::string& iconPath,
			  const WString& text, WMenu *menu)
{
  WMenuItem *item = new WMenuItem(iconPath, text, 0, WMenuItem::LazyLoading);
  item->setMenu(menu);
  addItem(item);
  return item;
}