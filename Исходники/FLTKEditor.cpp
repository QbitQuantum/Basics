bool CFLTKEditor::HighlightLinePos(const char *pcFilename, int iInputPos)
{
	if (iInputPos < 0)
		return false;

	int iTextPos, iLineStart, iLineEnd;
	char pcSearchName[300], *pcPoint;
	string sName;

	strncpy(pcSearchName, pcFilename, 299);
	if ((pcPoint = strstr(pcSearchName, ".clu")))
	{
		*pcPoint = 0;
	}

//	if (GetFilename().size() == 0)
		sName = GetPath() + GetName();
//	else
//		sName = GetFilename();

	if (pcSearchName != sName)
	{
		int i, iCount = m_mEditorData.Count();

		for (i = 0; i < iCount; i++)
		{
			//sName = m_mEditorData[i].m_sFilename;
			//if (sName.size() == 0)
			//{
				sName = m_mEditorData[i].m_sPath + m_mEditorData[i].m_sName;
			//}

			if (sName == pcSearchName)
			{
				SetCurEditor(i);
				m_pFileChoice->value(i);
				break;
			}
		}

		// File not opened yet
		if (i == iCount)
		{
			sName = pcSearchName;
			sName = sName + ".clu";
			CFLTKEditor::New();
			CFLTKEditor::LoadFile(sName.c_str());
			UpdateFileList();
		}
	}

	//iTextPos = GetTextBuffer()->skip_lines(0, iLine-1);
	iTextPos = iInputPos + 1;
	if (iTextPos >= GetTextBuffer()->length())
		iTextPos = GetTextBuffer()->length()-2;

	iLineStart = GetTextBuffer()->line_start(iTextPos);
	iLineEnd = GetTextBuffer()->line_end(iTextPos);
	GetTextBuffer()->select(iLineStart, iLineEnd);

	GetEditor()->insert_position(iTextPos);
	GetEditor()->show_insert_position();

	GetTextBuffer()->call_modify_callbacks();

	return true;
}