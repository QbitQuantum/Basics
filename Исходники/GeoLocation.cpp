void
GeoLocation::Run(const String& command) {
	if(!command.IsEmpty()) {
		Uri commandUri;
		commandUri.SetUri(command);
		String method = commandUri.GetHost();
		StringTokenizer strTok(commandUri.GetPath(), L"/");
		if(strTok.GetTokenCount() > 1) {
			strTok.GetNextToken(callbackId);
			AppLogDebug("Method %S, CallbackId: %S", method.GetPointer(), callbackId.GetPointer());
		}
		AppLogDebug("Method %S, Callback: %S", method.GetPointer(), callbackId.GetPointer());
		// used to determine callback ID
		if(method == L"com.phonegap.Geolocation.watchPosition" && !callbackId.IsEmpty() && !IsWatching()) {
			AppLogDebug("watching position...");
			StartWatching();
		}
		if(method == L"com.phonegap.Geolocation.stop" && IsWatching()) {
			AppLogDebug("stop watching position...");
			StopWatching();
		}
		if(method == L"com.phonegap.Geolocation.getCurrentPosition" && !callbackId.IsEmpty() && !IsWatching()) {
			AppLogDebug("getting current position...");
			GetLastKnownLocation();
		}
		AppLogDebug("GeoLocation command %S completed", command.GetPointer());
	}
}