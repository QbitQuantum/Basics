void CEmulatorCmd::StartLoop()
{
	static CString msg("Enter command: [Press '?' for list of available commands]\n");
	static CString input;
	while(true)
	{
		CUtils::WaitForInput(input, msg, false);
		input.ToLower();
		if(input == "q"){
			break;
		}else if(input == "?"){
			PrintAvailableCmds();
		}else if(input == "p"){
			CEIBEmulator::GetInstance().GetDB().Print();
		}else if(input == "s"){
			HandleSendCommand();
		}else if (input == "d"){
			CEIBEmulator::GetInstance().GetHandler().DisconnectClients();
		}else{
			LOG_SCREEN("Unknown command. [Press '?' for list of available commands]\n");
		}

	}
}