void MainMenuBar::reload()
{
  setMenu(NULL);

  // Reload all menus.
  AppMenus::instance()->reload();

  setMenu(AppMenus::instance()->getRootMenu());
}