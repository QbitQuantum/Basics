void
Notification::Run(const String& command) {
	if(!command.IsEmpty()) {
		Uri commandUri;
		commandUri.SetUri(command);
		String method = commandUri.GetHost();
		StringTokenizer strTok(commandUri.GetPath(), L"/");
		if(strTok.GetTokenCount() < 1) {
			AppLogException("Not enough params");
			return;
		}
		if((method == L"com.phonegap.Notification.alert" || method == L"com.phonegap.Notification.confirm")) {
			strTok.GetNextToken(callbackId);
			AppLogDebug("%S %S", method.GetPointer(), callbackId.GetPointer());
			if(!callbackId.IsEmpty()) {
				Dialog();
			}
		} else if(method == L"com.phonegap.Notification.vibrate") {
			long duration;
			String durationStr;

			strTok.GetNextToken(durationStr);
			AppLogDebug("%S %S", method.GetPointer(), durationStr.GetPointer());
			// Parsing duration
			result r = Long::Parse(durationStr, duration);
			if(IsFailed(r)) {
				AppLogException("Could not parse duration");
				return;
			}
			Vibrate(duration);
		} else if(method == L"com.phonegap.Notification.beep") {
			int count;
			String countStr;

			strTok.GetNextToken(countStr);
			AppLogDebug("%S %S", method.GetPointer(), countStr.GetPointer());
			// Parsing count
			result r = Integer::Parse(countStr, count);
			if(IsFailed(r)) {
				AppLogException("Could not parse count");
				return;
			}

			Beep(count);
		}
	}
}