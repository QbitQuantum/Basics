/*
 * MenuSpellChosen:  The spell with the given command id in the spell menu was chosen.
 */
void MenuSpellChosen(int id)
{
   int len, num=0, index=0, i;
   char item_name[MAXRSCSTRING + 1];
   spell *sp;
   HMENU submenu = NULL;

   if (spell_menu == NULL)
      return;


   for (i=0; i < num_schools; i++)
   {
      submenu = submenus[i];
      if (submenu)
      {
	 num = GetMenuItemCount(submenu);

	 // Look for menu item matching command id
	 for (index = 0; index < num; index++)
	 {
	    if (GetMenuItemID(submenu, index) == (UINT) id)
	    break;
	 }
	 if (index != num)
	    break;
      }
   }

   if (index == num)
   {
      debug(("MenuSpellChosen couldn't find menu id #%d\n", id));
      return;
   }

   len = GetMenuString(submenu, index, item_name, MAXRSCSTRING, MF_BYPOSITION);
   if (len == 0)
   {
      debug(("MenuSpellChosen get spell #%d from menu\n", index));
      return;
   }
   sp = FindSpellByName(item_name);
   if (sp == SPELL_NOMATCH || sp == SPELL_AMBIGUOUS)
   {
      debug(("MenuSpellChosen couldn't find spell %s\n", item_name));
      return;
   }

   PerformAction(A_CASTSPELL, sp);
}