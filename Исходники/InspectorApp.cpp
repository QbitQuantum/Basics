void
InspectorApp::AddToTranslatorsList(const char *folder, int32 group)
{
	BDirectory dir;
	if (dir.SetTo(folder) == B_OK) {
	
		BEntry ent;
		while (dir.GetNextEntry(&ent) == B_OK) {
			BPath path;
			if (ent.GetPath(&path) == B_OK)
				flstTranslators.AddItem(
					new BTranslatorItem(path.Leaf(), path.Path(), group));
		}	
	}
}