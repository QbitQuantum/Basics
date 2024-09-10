CDoc::CDoc(const char* mimetype, BLooper *target, const entry_ref *doc)
	: fDocIO(NULL)
	, fSavePanel(NULL)
	, fMimeType(mimetype ? mimetype : "")
	, fDirty(false)
	, fReadOnly(false)
	, fEncoding(B_UNICODE_UTF8)
	, fLineEndType(kle_LF)
{
	fDocIO = new CLocalDocIO(this, doc, target);
	FailNil(fDocIO);
	if (doc)
	{
		BEntry e;
		FailOSErr(e.SetTo(doc, true));
		FailOSErr(e.GetParent(&gCWD));

		BNode node;
		FailOSErr(node.SetTo(doc));

		struct stat st;
		FailOSErr(node.GetStat(&st));

		fReadOnly = !((gUid == st.st_uid && (S_IWUSR & st.st_mode))
						||	(gGid == st.st_gid && (S_IWGRP & st.st_mode))
						||	(S_IWOTH & st.st_mode));

		char s[NAME_MAX];
		if (BNodeInfo(&node).GetType(s) == B_OK)
			fMimeType = s;
	}
	sfDocList.push_back(this);
}