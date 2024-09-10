void CommandManager::HandleMenuOpen(wxMenuEvent &evt)
{
   // Ensure we have a menu and that it's a top-level menu.
   wxMenu *m = evt.GetMenu();
   if (!m || m->GetParent())
      return;

   // Windows does not send a CLOSE event if you move from one 
   // top-level menu to another, so simulate it.
   if (mOpenMenu) {
      wxMenuEvent dummy;
      HandleMenuClose(dummy);
   }

   // Remember this menu
   mOpenMenu = m;

   // Turn on the accelerators
   ToggleAccels(m, true);

   return;
}