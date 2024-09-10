__kextdll bool __cdecl ping(mod_pipe * monPipe, vector<wstring> * mesArguments)
{
	bool sendOk = sendTo(monPipe, L"pong");
	
	for(vector<wstring>::iterator monArgument = mesArguments->begin(); monArgument != mesArguments->end() && sendOk; monArgument++)
	{
		wstring maReponse = L" - argument:";
		maReponse.append(*monArgument);
		sendOk = sendTo(monPipe, maReponse);
	}
	
	if(sendOk)
		sendOk = sendTo(monPipe, L"\n");
	
	return sendOk;
}