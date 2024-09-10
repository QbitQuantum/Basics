void MenuCreator::populatePluginMenu(std::string pluginId, PluginMenu item, IIdGenerator* idgenerator)
{
    int index = getParentMenuIndex(item.mParentMenu);
    if (-1 != index)
    {
        CMenu* menu = mMainMenu->GetSubMenu(index); //TODO::nullpointer check
        INT COUNT = menu->GetMenuItemCount();
for (auto itemMenu : item.menuList)
        {
            populateMenu(pluginId, menu, itemMenu, idgenerator);
        }
        COUNT = menu->GetMenuItemCount();
        CMenu* subMenu = menu->GetSubMenu(19);
        // COUNT = subMenu->GetMenuItemCount();
        COUNT++;
    }
}