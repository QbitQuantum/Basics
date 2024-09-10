PolycodeEditor *PolycodeEditorManager::openFile(OSFileEntry file) {

    // NOCMAKE_TODO:
    /*
	if(!Services()->getCore()->fileExists(file.fullPath)) {
		return NULL;
	}
*/
	PolycodeEditor *editor = getEditorForPath(file.fullPath);	
	if(editor) {
		return editor;
	} else {
		editor = createEditorForExtension(file.extension);
		if(editor) {
			editor->parentProject = projectManager->getActiveProject();
			if(!editor->openFile(file)) {
				delete editor;
				editor = NULL;
			}
		}
	}
	return editor;
}