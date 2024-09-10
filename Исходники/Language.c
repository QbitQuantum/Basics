/*
 * LanguageExit:  Free language menu when game exited.
 */
void LanguageExit(void)
{
   // Remove "Language" menu.
   if (language_menu != NULL)
   {
      RemoveMenu(cinfo->main_menu, MENU_POSITION_LANGUAGE, MF_BYPOSITION);
      DrawMenuBar(cinfo->hMain);
      DestroyMenu(language_menu);
   }

   language_menu = NULL;
}