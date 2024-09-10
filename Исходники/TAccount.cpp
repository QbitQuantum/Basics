/*
	TAccount: Account Management
*/
bool TAccount::meetsConditions( CString fileName, CString conditions )
{
	const char* conditional[] = { ">=", "<=", "!=", "=", ">", "<" };

	// Load and check if the file is valid.
	std::vector<CString> file;
	file = CString::loadToken(fileName, "\n", true);
	if (file.size() == 0 || (file.size() != 0 && file[0] != "GRACC001"))
		return false;

	// Load the conditions into a string list.
	std::vector<CString> cond;
	conditions.removeAllI("'");
	conditions.replaceAllI("%", "*");
	cond = conditions.tokenize(",");
	bool* conditionsMet = new bool[cond.size()];
	memset((void*)conditionsMet, 0, sizeof(bool) * cond.size());

	// Go through each line of the loaded file.
	for (std::vector<CString>::iterator i = file.begin(); i != file.end(); ++i)
	{
		int sep = (*i).find(' ');
		CString section = (*i).subString(0, sep);
		CString val = (*i).subString(sep + 1).removeAll("\r");
		section.trimI();
		val.trimI();

		// Check each line against the conditions specified.
		for (unsigned int j = 0; j < cond.size(); ++j)
		{
			int cond_num = -1;

			// Read out the name and value.
			cond[j].setRead(0);

			// Find out what conditional we are using.
			for (int k = 0; k < 6; ++k)
			{
				if (cond[j].find(conditional[k]) != -1)
				{
					cond_num = k;
					k = 6;
				}
			}
			if (cond_num == -1) continue;

			CString cname = cond[j].readString(conditional[cond_num]);
			CString cvalue = cond[j].readString("");
			cname.trimI();
			cvalue.trimI();
			cond[j].setRead(0);

			// Now, do a case-insensitive comparison of the section name.
#ifdef WIN32
			if (_stricmp(section.text(), cname.text()) == 0)
#else
			if (strcasecmp(section.text(), cname.text()) == 0)
#endif
			{
				switch (cond_num)
				{
					case 0:
					case 1:
					{
						// 0: >=
						// 1: <=
						// Check if it is a number.  If so, do a number comparison.
						bool condmet = false;
						if (val.isNumber())
						{
							double vNum[2] = { atof(val.text()), atof(cvalue.text()) };
							if (((cond_num == 1) ? (vNum[0] <= vNum[1]) : (vNum[0] >= vNum[1])))
							{
								conditionsMet[j] = true;
								condmet = true;
							}
						}
						else
						{
							// If not a number, do a string comparison.
							int ret = strcmp(val.text(), cvalue.text());
							if (((cond_num == 1) ? (ret <= 0) : (ret >= 0)))
							{
								conditionsMet[j] = true;
								condmet = true;
							}
						}

						// No conditions met means we see if we can fail.
						if (condmet == false)
						{
							CString cnameUp = cname.toUpper();
							if (!(cnameUp == "CHEST" || cnameUp == "WEAPON" ||
								cnameUp == "FLAG" || cnameUp == "FOLDERRIGHT"))
								goto condAbort;
						}
						break;
					}

					case 4:
					case 5:
					{
						// 4: >
						// 5: <
						bool condmet = false;
						if (val.isNumber())
						{
							double vNum[2] = { atof(val.text()), atof(cvalue.text()) };
							if (((cond_num == 5) ? (vNum[0] < vNum[1]) : (vNum[0] > vNum[1])))
							{
								conditionsMet[j] = true;
								condmet = true;
							}
						}
						else
						{
							int ret = strcmp(val.text(), cvalue.text());
							if (((cond_num == 5) ? (ret < 0) : (ret > 0)))
							{
								conditionsMet[j] = true;
								condmet = true;
							}
						}

						if (condmet == false)
						{
							CString cnameUp = cname.toUpper();
							if (!(cnameUp == "CHEST" || cnameUp == "WEAPON" ||
								cnameUp == "FLAG" || cnameUp == "FOLDERRIGHT"))
								goto condAbort;
						}
						break;
					}

					case 2:
					{
						// 2: !=
						// If we find a match, return false.
						if (val.isNumber())
						{
							double vNum[2] = { atof(val.text()), atof(cvalue.text()) };
							if (vNum[0] == vNum[1]) goto condAbort;
							conditionsMet[j] = true;
						}
						else
						{
							if (val.match(cvalue.text()) == true) goto condAbort;
							conditionsMet[j] = true;
						}
						break;
					}

					case 3:
					default:
					{
						// 0 - equals
						// If it returns false, don't include this account in the search.
						bool condmet = false;
						if (val.isNumber())
						{
							double vNum[2] = { atof(val.text()), atof(cvalue.text()) };
							if (vNum[0] == vNum[1])
							{
								conditionsMet[j] = true;
								condmet = true;
							}
						}
						else
						{
							if (val.match(cvalue.text()) == true)
							{
								conditionsMet[j] = true;
								condmet = true;
							}
						}

						if (condmet == false)
						{
							CString cnameUp = cname.toUpper();
							if (!(cnameUp == "CHEST" || cnameUp == "WEAPON" ||
								cnameUp == "FLAG" || cnameUp == "FOLDERRIGHT"))
								goto condAbort;
						}
						break;
					}
				}
			}
		}
	}

	// Check if all the conditions were met.
	for (unsigned int i = 0; i < cond.size(); ++i)
		if (conditionsMet[i] == false) goto condAbort;

	// Clean up.
	delete [] conditionsMet;
	return true;

condAbort:
	delete [] conditionsMet;
	return false;
}