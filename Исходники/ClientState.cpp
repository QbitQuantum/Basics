 bool operator()(string signal) {
     GuiConsoleOutput cout = GG.console->output();
     string input = GG.console->getInput();
     // cout << "Received command " << input << std::endl;
     // send message
     mClient->Send(input.c_str(), (int) input.length()+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
     return false;
 }