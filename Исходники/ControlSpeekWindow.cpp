void ControlSpeekWindow::PreparePages()
{
	char* newtext = new char[strlen(character->ActiveConversation->ActiveNode->Statement)+1];
	int linecount = 0;
	char* token = nullptr;
	char* nextToken = nullptr;
	char newpage[512];

	currentpage = 0;
	for(int i=pages.size()-1; i>=0; i--)
	{
		delete pages.back();
		pages.pop_back();
	}

	strcpy_s(newtext, strlen(character->ActiveConversation->ActiveNode->Statement)+1, character->ActiveConversation->ActiveNode->Statement);
	token = strtok_s(newtext, "\n", &nextToken);
	while (token != nullptr)
	{
		if(linecount == 0)
		{
			strcpy_s(newpage, 512, "");
		}
		
		strcat_s(newpage, 512, token);
		strcat_s(newpage, 512, "\n");
		token = strtok_s(nullptr, "\n", &nextToken);
		linecount++;

		if(linecount == 5)
		{
			pages.push_back(new char[strlen(newpage)+1]);
			strcpy_s(pages.back(), strlen(newpage)+1, newpage);
			linecount = 0;
		}
	}

	if(linecount != 0)
	{
		pages.push_back(new char[strlen(newpage)+1]);
		strcpy_s(pages.back(), strlen(newpage)+1, newpage);
	}

	delete newtext;
	delete token;
};