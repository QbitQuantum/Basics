void exceptionMessage(const exception &excp) {
	string message, title;
	showCursor(true);

	message += "ERROR(S):\n\n";
	message += excp.what();

	title = "Error: Unhandled Exception";
	MessageBox(NULL, message.c_str(), title.c_str(), MB_ICONSTOP | MB_OK | MB_TASKMODAL);
}