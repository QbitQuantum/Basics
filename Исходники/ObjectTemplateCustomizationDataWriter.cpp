bool ObjectTemplateCustomizationDataWriter::writeToFile(const std::string &pathName, bool allowOverwrite)
{
	//-- Don't write anything if there's no data to write.
	bool hasData = false;

	if (!m_paletteColorData->empty())
		hasData = true;

	if (!m_rangedIntData->empty())
		hasData = true;

	if (!hasData)
	{
		DEBUG_REPORT_LOG(true, ("writeToFile(): no data: skipped writing [%s].\n", pathName.c_str()));
		return true;
	}

	//-- Handle no-overwrite case.
	if (!allowOverwrite)
	{
		FILE *const testFile = fopen(pathName.c_str(), "r");
		if (testFile != NULL)
		{
			fclose(testFile);
			DEBUG_REPORT_LOG(true, ("writeToFile(): overwrite attempt: skipped writing [%s] because it already exists and allowOverwrite == false.\n", pathName.c_str()));
			return false;
		}
	}

	//-- open file
	FILE *const file = fopen(pathName.c_str(), "w");
	if (!file)
	{
		WARNING(true, ("failed to create file [%s].", pathName.c_str()));
		return false;
	}

	//-- sort the output data
	m_paletteColorData->sort();
	m_rangedIntData->sort();

	//-- write palette color variables
	fprintf(file, "paletteColorCustomizationVariables = [");
	{
		int i = 0;
		int const count = static_cast<int>(m_paletteColorData->size());

		const StringList::iterator endIt = m_paletteColorData->end();
		for (StringList::iterator it = m_paletteColorData->begin(); it != endIt; ++it, ++i)
		{
			if (i == (count - 1))
			{
				// -- Fixup last entry to use ] in place of final comma.
				std::string::size_type position = it->rfind(',');
				DEBUG_FATAL(static_cast<int>(position) == static_cast<int>(std::string::npos), ("bad data, where's the final comma?"));

				(*it)[position] = ']';
			}

			fprintf(file, "\n  %s", it->c_str());
		}
	}
	if (m_paletteColorData->empty())
		fprintf(file, "]");
	fprintf(file, "\n\n");

	//-- write ranged int variables
	fprintf(file, "rangedIntCustomizationVariables = [");
	{
		int i = 0;
		int const count = static_cast<int>(m_rangedIntData->size());

		const StringList::iterator endIt = m_rangedIntData->end();
		for (StringList::iterator it = m_rangedIntData->begin(); it != endIt; ++it, ++i)
		{
			if (i == (count - 1))
			{
				// -- Fixup last entry to use ] in place of final comma.
				std::string::size_type position = it->rfind(',');
				DEBUG_FATAL(static_cast<int>(position) == static_cast<int>(std::string::npos), ("bad data, where's the final comma?"));

				(*it)[position] = ']';
			}

			fprintf(file, "\n  %s", it->c_str());
		}
	}
	if (m_rangedIntData->empty())
		fprintf(file, "]");
	fprintf(file, "\n\n");

	fclose(file);

	//-- return success
	return true;
}