void
BepdfApplication::UpdateFileAttributes(PDFDoc *doc, entry_ref *ref) {
	BNode node(ref);
	if (node.InitCheck() != B_OK) return;

	const bool force_overwrite = (modifiers() & B_COMMAND_KEY) == B_COMMAND_KEY;

	if (force_overwrite) {
		for (int i = 0; gAttrInfo[i].name; i++) {
			node.RemoveAttr(gAttrInfo[i].name);
		}
	}

	int32 pages = (int32)doc->getNumPages();
	UpdateAttr(node, "META:pages", B_INT32_TYPE, 0, &pages, sizeof(int32));
	bool b = doc->isLinearized();
	UpdateAttr(node, "PDF:linearized", B_BOOL_TYPE, 0, &b, sizeof(b));
	double d = doc->getPDFVersion();
	UpdateAttr(node, "PDF:version", B_DOUBLE_TYPE, 0, &d, sizeof(d));

	Object obj;
	if (doc->getDocInfo(&obj) && obj.isDict()) {
		Dict *dict = obj.getDict();
		for (int i = 0; gAttrInfo[i].name; i++) {
			time_t time;
			if (gAttrInfo[i].pdf_name == NULL) continue;
			BString *s = FileInfoWindow::GetProperty(dict, gAttrInfo[i].pdf_name, &time);
			if (s) {
				if (gAttrInfo[i].type_code == B_TIME_TYPE) {
					if (time != 0) {
						UpdateAttr(node, gAttrInfo[i].name, B_TIME_TYPE, 0, &time, sizeof(time));
					}
				} else {
					UpdateAttr(node, gAttrInfo[i].name, B_STRING_TYPE, 0, (void*)s->String(), s->Length()+1);
				}
				delete s;
			}
		}
	}
	obj.free();
}