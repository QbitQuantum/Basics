	void LogTraceListener::removeFile(QDir& dir, const string& fileName, int days)
	{
		string name = fileName;
		if (strcmp(_fullFileName.c_str(), name.c_str()) != 0)
		{
			const QDateTime now = QDateTime::currentDateTime();

			if (!_prefix.empty())
			{
				Convert::replaceStr(name, _prefix, "");
			}
			if (!_suffix.empty())
			{
				Convert::replaceStr(name, _suffix, "");
			}
			Convert::replaceStr(name, ".log", "");
			QDate date = Convert::parseDate(name);
			int sec = now.secsTo(date);
			if (!date.isNull() && date.isValid() &&
				sec < 0 && (-sec > days * 24 * 3600))
			{
				bool result = dir.remove(fileName.c_str());
				if(result)
				{
					Trace::WriteFormatLine(Resources::RemoveLogFilesSuccessfullyStr, fileName.c_str());
				}
				else
				{
					Trace::WriteFormatLine(Resources::FailedtoRemoveLogFilesStr, fileName.c_str());
				}
			}
		}
	}