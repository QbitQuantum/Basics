BBitmap *getIconFromResources(const char *icon_resname) {
	BBitmap *bmp = NULL;
	BResources *res = be_app->AppResources();
	if (res->HasResource('BBMP',icon_resname)) {
		printf("has resource bitmap [%s]\n",icon_resname);
		BMessage msg;
		size_t len;
		char *buf;
		buf = (char *)res->LoadResource('BBMP', icon_resname, &len);
//					printf("loaded,len=%i\n",len);
		msg.Unflatten(buf);
		bmp = new BBitmap(&msg);
	}
	return bmp;
}