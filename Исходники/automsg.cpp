/**
 * Main Automessage menu.  Displays the auto message then queries for input.
 */
void do_automessage() {
  std::stringstream lockFileStream;
  lockFileStream << syscfg.gfilesdir << LOCKAUTO_MSG;
  std::string automessageLockFile = lockFileStream.str();

  std::stringstream autoMessageStream;
  autoMessageStream << syscfg.gfilesdir << AUTO_MSG;
  std::string autoMessageFile = autoMessageStream.str();

  // initally show the auto message
  read_automessage();

  bool done = false;
  do {
    GetSession()->bout.NewLine();
    char cmdKey = ShowAMsgMenuAndGetInput(automessageLockFile);
    switch (cmdKey) {
    case 'Q':
      done = true;
      break;
    case 'R':
      read_automessage();
      break;
    case 'W':
      write_automessage();
      break;
    case 'A': {
      grab_quotes(NULL, NULL);
      WStatus *pStatus = GetApplication()->GetStatusManager()->GetStatus();
      if (pStatus->GetAutoMessageAuthorUserNumber() > 0) {
        strcpy(irt, "Re: AutoMessage");
        email(pStatus->GetAutoMessageAuthorUserNumber(), 0, false, pStatus->IsAutoMessageAnonymous() ? anony_sender : 0);
      }
      delete pStatus;
    }
    break;
    case 'D':
      GetSession()->bout << "\r\n|#3Delete Auto-message, Are you sure? ";
      if (yesno()) {
        WFile::Remove(autoMessageFile);
      }
      GetSession()->bout.NewLine(2);
      break;
    case 'L':
      if (WFile::Exists(automessageLockFile)) {
        GetSession()->bout << "\r\n|#3Message is already locked.\r\n\n";
      } else {
        GetSession()->bout <<  "|#9Do you want to lock the Auto-message? ";
        if (yesno()) {
          /////////////////////////////////////////////////////////
          // This makes a file in your GFILES dir 1 bytes long,
          // to tell the board if it is locked or not. It consists
          // of a space.
          //
          WTextFile lockFile(automessageLockFile, "w+t");
          lockFile.WriteChar(' ');
          lockFile.Close();
        }
      }
      break;
    case 'U':
      if (!WFile::Exists(automessageLockFile)) {
        GetSession()->bout << "Message not locked.\r\n";
      } else {
        GetSession()->bout << "|#5Unlock message? ";
        if (yesno()) {
          WFile::Remove(automessageLockFile);
        }
      }
      break;
    }
  } while (!done && !hangup);
}