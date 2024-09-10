	void IncludeFile(int line_nr, const char *filename)
	{
		// Read the included file into a new TBNode and then
		// move all the children to m_target_node.
		TBTempBuffer include_filename;
		include_filename.AppendPath(m_filename);
		include_filename.AppendString(filename);
		TBNode content;
		if (content.ReadFile(include_filename.GetData()))
		{
			while (TBNode *content_n = content.GetFirstChild())
			{
				content.Remove(content_n);
				m_target_node->Add(content_n);
			}
		}
		else
		{
			TBStr err;
			err.SetFormatted("Referenced file \"%s\" was not found!", include_filename.GetData());
			OnError(line_nr, err);
		}
	}