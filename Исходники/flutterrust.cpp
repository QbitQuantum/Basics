bool App::OnInit() {
   SetAppName(u8"flutterrust");
   SetAppDisplayName(u8"flutterrust");

   const wxFileName exeFileName{wxStandardPaths::Get().GetExecutablePath()};
   const std::string exePath = exeFileName.GetPath().ToStdString();
   try {
      Creature::loadTypes(exePath + static_cast<char>(wxFileName::GetPathSeparator()) +
                          u8"CreatureTable.txt");
      mainFrame = new MainFrame{exePath};
   } catch (const std::exception& e) {
      wxMessageDialog dialog{nullptr, u8"Exception caught.  Terminating.\n",
                             u8"Fatal error", wxICON_ERROR | wxOK};
      dialog.SetExtendedMessage(std::string{typeid(e).name()} + ": \"" + e.what() + '"');
      dialog.ShowModal();
      return false;  // Exit the application immediately.
   } catch (...) {
      wxMessageDialog(nullptr, u8"Unknown exception caught.  Terminating.",
                      u8"Fatal error", wxICON_ERROR | wxOK)
          .ShowModal();
      return false;
   }

   mainFrame->Show(true);
   SetTopWindow(mainFrame);

   return true;  // Continue processing.
}