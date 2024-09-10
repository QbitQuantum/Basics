void insertIndexes(std::vector<std::string> items, PaletteFilterFxRenderData *t)
{
#ifdef _WIN32
	for (int i = 0; i < (int)items.size(); i++) {
		char *starttoken, *endtoken;
		char subseps[] = "-";
		std::string tmp = items[i];
		char *context = 0;
		starttoken = strtok_s((char *)tmp.c_str(), subseps, &context);
		endtoken = strtok_s(NULL, subseps, &context);
		if (!endtoken && isInt(starttoken)) {
			int index;
			index = toInt(starttoken);
			t->m_colors.insert(index);
		} else {
			if (isInt(starttoken) && isInt(endtoken)) {
				int start, end;
				start = toInt(starttoken);
				end = toInt(endtoken);
				for (int i = start; i <= end; i++)
					t->m_colors.insert(i);
			}
		}
	}
#else
	for (int i = 0; i < (int)items.size(); i++) {
		char *starttoken, *endtoken;
		char subseps[] = "-";
		std::string tmp = items[i];
		starttoken = strtok((char *)tmp.c_str(), subseps);
		endtoken = strtok(NULL, subseps);
		if (!endtoken && isInt(starttoken)) {
			int index;
			index = toInt(starttoken);
			t->m_colors.insert(index);
		} else {
			if (isInt(starttoken) && isInt(endtoken)) {
				int start, end;
				start = toInt(starttoken);
				end = toInt(endtoken);
				for (int i = start; i <= end; i++)
					t->m_colors.insert(i);
			}
		}
	}
#endif
}