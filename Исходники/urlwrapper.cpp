void
UrlWrapper::RefsReceived(BMessage* msg)
{
	char buff[B_PATH_NAME_LENGTH];
	int32 index = 0;
	entry_ref ref;
	char* args[] = { const_cast<char*>("urlwrapper"), buff, NULL };
	status_t err;

	while (msg->FindRef("refs", index++, &ref) == B_OK) {
		BFile f(&ref, B_READ_ONLY);
		BNodeInfo ni(&f);
		BString mimetype;
		BString extension(ref.name);
		extension.Remove(0, extension.FindLast('.') + 1);
		if (f.InitCheck() == B_OK && ni.InitCheck() == B_OK) {
			ni.GetType(mimetype.LockBuffer(B_MIME_TYPE_LENGTH));
			mimetype.UnlockBuffer();

			// Internet Explorer Shortcut
			if (mimetype == "text/x-url" || extension == "url") {
				// http://filext.com/file-extension/URL
				// http://www.cyanwerks.com/file-format-url.html
				off_t size;
				if (f.GetSize(&size) < B_OK)
					continue;
				BString contents;
				BString url;
				if (f.ReadAt(0LL, contents.LockBuffer(size), size) < B_OK)
					continue;
				contents.UnlockBuffer();
				while (contents.Length()) {
					BString line;
					int32 cr = contents.FindFirst('\n');
					if (cr < 0)
						cr = contents.Length();
					//contents.MoveInto(line, 0, cr);
					contents.CopyInto(line, 0, cr);
					contents.Remove(0, cr+1);
					line.RemoveAll("\r");
					if (!line.Length())
						continue;
					if (!line.ICompare("URL=", 4)) {
						line.MoveInto(url, 4, line.Length());
						break;
					}
				}
				if (url.Length()) {
					BPrivate::Support::BUrl u(url.String());
					args[1] = (char*)u.String();
					mimetype = kURLHandlerSigBase;
					mimetype += u.Proto();
					err = be_roster->Launch(mimetype.String(), 1, args + 1);
					if (err != B_OK && err != B_ALREADY_RUNNING)
						err = be_roster->Launch(kAppSig, 1, args + 1);
					continue;
				}
			}
			if (mimetype == "text/x-webloc" || extension == "webloc") {
				// OSX url shortcuts
				// XML file + resource fork
				off_t size;
				if (f.GetSize(&size) < B_OK)
					continue;
				BString contents;
				BString url;
				if (f.ReadAt(0LL, contents.LockBuffer(size), size) < B_OK)
					continue;
				contents.UnlockBuffer();
				int state = 0;
				while (contents.Length()) {
					BString line;
					int32 cr = contents.FindFirst('\n');
					if (cr < 0)
						cr = contents.Length();
					contents.CopyInto(line, 0, cr);
					contents.Remove(0, cr+1);
					line.RemoveAll("\r");
					if (!line.Length())
						continue;
					int32 s, e;
					switch (state) {
						case 0:
							if (!line.ICompare("<?xml", 5))
								state = 1;
							break;
						case 1:
							if (!line.ICompare("<plist", 6))
								state = 2;
							break;
						case 2:
							if (!line.ICompare("<dict>", 6))
								state = 3;
							break;
						case 3:
							if (line.IFindFirst("<key>URL</key>") > -1)
								state = 4;
							break;
						case 4:
							if ((s = line.IFindFirst("<string>")) > -1
								&& (e = line.IFindFirst("</string>")) > s) {
								state = 5;
								s += 8;
								line.MoveInto(url, s, e - s);
								break;
							} else
								state = 3;
							break;
						default:
							break;
					}
					if (state == 5) {
						break;
					}
				}
				if (url.Length()) {
					BPrivate::Support::BUrl u(url.String());
					args[1] = (char*)u.String();
					mimetype = kURLHandlerSigBase;
					mimetype += u.Proto();
					err = be_roster->Launch(mimetype.String(), 1, args + 1);
					if (err != B_OK && err != B_ALREADY_RUNNING)
						err = be_roster->Launch(kAppSig, 1, args + 1);
					continue;
				}
			}

			// NetPositive Bookmark or any file with a META:url attribute
			if (f.ReadAttr("META:url", B_STRING_TYPE, 0LL, buff,
				B_PATH_NAME_LENGTH) > 0) {
				BPrivate::Support::BUrl u(buff);
				args[1] = (char*)u.String();
				mimetype = kURLHandlerSigBase;
				mimetype += u.Proto();
				err = be_roster->Launch(mimetype.String(), 1, args + 1);
				if (err != B_OK && err != B_ALREADY_RUNNING)
					err = be_roster->Launch(kAppSig, 1, args + 1);
				continue;
			}
		}
	}
}