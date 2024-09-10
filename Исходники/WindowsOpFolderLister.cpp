OP_STATUS
WindowsOpFolderLister::Construct(const uni_char* path, const uni_char* pattern)
{
	m_find_handle = INVALID_HANDLE_VALUE;

	RETURN_IF_ERROR(m_path_pattern.Set(path));
	if (!m_path_pattern.Length() || m_path_pattern[m_path_pattern.Length() - 1] != '\\')
	{
		RETURN_IF_ERROR(m_path_pattern.Append("\\"));
	}

	m_path = OP_NEWA(uni_char, m_path_pattern.Length() + MAX_PATH + 1);
	if (m_path == NULL) return OpStatus::ERR_NO_MEMORY;
	m_path_length = m_path_pattern.Length();
	uni_strcpy(m_path, m_path_pattern.CStr());
	RETURN_IF_ERROR(m_path_pattern.Append(pattern));

	if (!m_path_pattern.Compare(UNI_L("\\*")))
	{
		if ((m_drives = GetLogicalDrives()) == 0)
			return OpStatus::ERR;
	}
	else if (m_path_pattern[0] == '\\' && m_path_pattern[1] != '\\') // remove \ before drive name if present but not from network paths
	{
		m_path_pattern.Delete(0, 1);
	}

	return OpStatus::OK;

}