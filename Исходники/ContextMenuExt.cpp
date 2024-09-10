void ContextMenuExt::UpdateSelectionFlags(std::wstring currentPath)
{
	// ONE: number of files
	m_selectionOnlyOne = (m_files.size() == 1);

	// FOLDER: if folder flag not set, check whether last path is a folder
	bool isFolder = PathIsDirectoryW(currentPath.c_str()) != false;
	if (!m_selectionHasFolders && isFolder){
		m_selectionHasFolders = true;
	}

	// FILE: if file flag not set, check whether last path is a file
	if (!m_selectionHasFiles && !isFolder) {
		m_selectionHasFiles = true;
	}
}