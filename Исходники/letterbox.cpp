void Letterbox::openParticularFile(const QString &filename)
{
	if (!filename.isEmpty())
	{
		if (m_modified)
		{
			switch (askToSave())
			{
				case 0:
					writeFile();

				case 1:
					break;

				case 2:
					return;
			}
		}

		m_filename = filename;
		loadFile();
	}
}