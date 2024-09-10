/**
 * Handles a user request to dump triggers to textual format.
 */
void OnFileTrigWrite(HWND dialog)
{
	char path[MAX_PATH] = "trigs.xml";

	// TODO: set the path to aokts directory.
	if (!GetSaveFileNameA(dialog, path, MAX_PATH))
		return;

	AutoFile textout(path, "w");
    std::ostringstream ss;
	scen.accept(TrigXmlVisitor(ss));
	fputs(ss.str().c_str(), textout.get());
}