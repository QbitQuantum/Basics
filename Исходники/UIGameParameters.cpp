void GameParamUserInterface::updateMenuItems(const GameType *gameType)
{
   TNLAssert(gameType, "Missing game type!");

   string filename = mLevelFilename;
   // Grab the level filename from the menuitem if it has been built already.
   // This let's us persist a changed filename without having to leave the menu first
   if(getMenuItemCount() > 0)
      filename = getMenuItem(1)->getValue();

   clearMenuItems();

   // Note that on some gametypes instructions[1] is NULL
   string instructs = string(gameType->getInstructionString()[0]) + 
                             (gameType->getInstructionString()[1] ?  string(" ") + gameType->getInstructionString()[1] : "");

   addMenuItem(new ToggleMenuItem("Game Type:",       
                                  getGameTypes(),
                                  getGameTypes().getIndex(gameType->getGameTypeName()),
                                  true,
                                  changeGameTypeCallback,
                                  instructs));


   addMenuItem(new TextEntryMenuItem("Filename:",                         // name
                                     filename,                            // val
                                     EditorUserInterface::UnnamedFile,    // empty val
                                     "File where this level is stored",   // help
                                     MAX_FILE_NAME_LEN));

   const Vector<string> *keys = gameType->getGameParameterMenuKeys();

   for(S32 i = 0; i < keys->size(); i++)
   {
      MenuItemMap::iterator iter = mMenuItemMap.find(keys->get(i));

      boost::shared_ptr<MenuItem> menuItem;

      if(iter != mMenuItemMap.end())      // What is this supposed to do?  I can't seem to make this condition occur.
         menuItem = iter->second;
      else                 // Item not found
      {
         menuItem = gameType->getMenuItem(keys->get(i));
         TNLAssert(menuItem, "Failed to make a new menu item!");

         mMenuItemMap.insert(pair<string, boost::shared_ptr<MenuItem> >(keys->get(i), menuItem));
      }

      addWrappedMenuItem(menuItem);
   }
}