QString EQStr::formatMessage(uint32_t formatid, const char* arguments, size_t argsLen) const
{
	QString tempStr;

	if (!m_messageStrings.contains(formatid))
	{
		tempStr.sprintf("Unknown: %04x: ", formatid);
		tempStr += QString::fromUtf8(arguments);

		size_t totalArgsLen = strlen(arguments) + 1;

		const char* curMsg;
		while (totalArgsLen < argsLen)
		{
			curMsg = arguments + totalArgsLen;
			tempStr += QString(", ") + QString::fromUtf8(curMsg);
			totalArgsLen += strlen(curMsg) + 1;
		}
	}
	else
	{
		QVector<QString> argList;
		argList.reserve(5); // reserve space for 5 elements to handle most common sizes

		size_t totalArgsLen = 0;
		while (totalArgsLen < argsLen)
		{
			const char* curArg = arguments + totalArgsLen;
			
			// insert argument into the argument list
			argList.push_back(QString::fromUtf8(curArg));
			totalArgsLen += strlen(curArg) + 1;
		}

		bool ok, ok2;
		int curPos;
		size_t substArg;
		int substArgValue;
		QString substFormatString;

		////////////////////////////
		// replace template (%T) arguments in formatted string
		QString formatString = m_messageStrings[formatid];
		QRegExp rxt("%T(\\d{1,3})", true, false);

		// find first template substitution
		curPos = rxt.search(formatString, 0);

		while (curPos != -1)
		{
			ok2 = false;
			substArg = rxt.cap(1).toInt(&ok);
			if (ok && (substArg <= argList.size()))
			{
				substArgValue = argList[substArg-1].toInt(&ok2);
			}

			// Find the message and replace, or skip over if not found.
			if (ok2 && m_messageStrings.contains(substArgValue))
				formatString.replace(curPos, rxt.matchedLength(), m_messageStrings[substArgValue]);
			else
				curPos += rxt.matchedLength();

			// find next substitution
			curPos = rxt.search(formatString, curPos);
		}

		////////////////////////////
		// now replace substitution arguments in formatted string
		// NOTE: not using QString::arg() because not all arguments are always used
		//       and it will do screwy stuff in this situation
		QRegExp rx("%(\\d{1,3})", true, false);

		// find first template substitution
		curPos = rx.search(formatString, 0);

		while (curPos != -1)
		{
			substArg = rx.cap(1).toInt(&ok);

			// replace substitution argument with argument from list
			if (ok && (substArg <= argList.size()))
				formatString.replace(curPos, rx.matchedLength(), argList[substArg-1]);
			else
				curPos += rx.matchedLength(); // if no such argument, skip over

			// find next substitution
			curPos = rx.search(formatString, curPos);
		}

		return formatString;
	}

	return tempStr;
}