int INIparser::getData(string filename, string data, string *output)
{
	filename = filename.toLower();
	if(!filename.contains(".ini"))
	{
		filename = filename + ".ini";
	}
	File file(filename);

	if(!file.exists())
	{
		// qDebug() << "File does not exists";
		return -1;
	}

	if(!file.open(QIODevice::ReadOnly))
	{
		// qDebug() << "Cannot open file";
		return -2;
	}

	string string = file.readAll();
	if(!string.contains(data + '='))
	{
		// qDebug() << "There is no data called " + data;
		return -3;
		file.close();
	}

	file.seek(0);			// Reset pos to start of file
	string = "";			// empty sting
	string temp = "";
	while(!string.contains(data + '='))
	{
		string = file.readLine();
		if(string.contains(data + '='))
		{
			int i = 0;
			while(string.at(i) != '=')
			{
				i++;
			}

			char end = 1;				// Avoid illegal memory acces
			if(!file.atEnd())
			{
				end = 3;				// Remove \r\n & avoid illegal memory acces
			}

			while(i < (string.length() - end))
			{
				i++;
				temp.append(string.at(i));
			}
		}
	}

	file.close();
	*output = temp;
	return 0;
}