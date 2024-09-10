void
TeamWindow::_HandleResolveMissingSourceFile(entry_ref& locatedPath)
{
	if (fActiveFunction != NULL) {
		LocatableFile* sourceFile = fActiveFunction->GetFunctionDebugInfo()
			->SourceFile();
		if (sourceFile != NULL) {
			BString sourcePath;
			sourceFile->GetPath(sourcePath);
			BString sourceFileName(sourcePath);
			int32 index = sourcePath.FindLast('/');
			if (index >= 0)
				sourceFileName.Remove(0, index + 1);

			BPath targetFilePath(&locatedPath);
			if (targetFilePath.InitCheck() != B_OK)
				return;

			if (strcmp(sourceFileName.String(), targetFilePath.Leaf()) != 0) {
				BString message;
				message.SetToFormat("The names of source file '%s' and located"
					" file '%s' differ. Use file anyway?",
					sourceFileName.String(), targetFilePath.Leaf());
				BAlert* alert = new(std::nothrow) BAlert(
					"Source path mismatch", message.String(), "Cancel", "Use");
				if (alert == NULL)
					return;

				int32 choice = alert->Go();
				if (choice <= 0)
					return;
			}
			fListener->SourceEntryLocateRequested(sourcePath,
				targetFilePath.Path());
			fListener->FunctionSourceCodeRequested(fActiveFunction);
		}
	}
}