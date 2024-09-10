void __cdecl Check_ThreadFunc(void *lpParam)
{
	InternetSetCookieA("https://mail.google.com/mail/", "GX", "");
	if (lpParam) {
		CheckMailInbox((Account *)lpParam);
		NotifyUser((Account *)lpParam);
	}
	else {
		for (int i = 0; i < acc_num && GetContactProto(acc[i].hContact); i++) {
			CheckMailInbox(&acc[i]);
			NotifyUser(&acc[i]);
		}
	}
}