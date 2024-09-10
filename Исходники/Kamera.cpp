void
Kamera::Run(const String& command) {
	if(!command.IsEmpty()) {
		Uri commandUri;
		commandUri.SetUri(command);
		String method = commandUri.GetHost();
		StringTokenizer strTok(commandUri.GetPath(), L"/");
		if(strTok.GetTokenCount() < 1) {
			AppLogException("Not enough params");
			return;
		}
		strTok.GetNextToken(callbackId);
		if(method == "com.phonegap.Camera.getPicture" && !callbackId.IsEmpty()) {
			GetPicture();
		}
	}
}