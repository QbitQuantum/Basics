static void loadTrophyData(char *filename)
{
	cJSON *root, *node;
	char *text;
	Trophy *t, *tail;
	int count[TROPHY_MAX];

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	text = readFile(filename);
	root = cJSON_Parse(text);

	tail = &game.trophyHead;
	
	memset(count, 0, sizeof(int) * TROPHY_MAX);

	for (node = root->child ; node != NULL ; node = node->next)
	{
		if (cJSON_GetObjectItem(node, "id")->valuestring[0] != '_')
		{
			t = malloc(sizeof(Trophy));
			memset(t, 0, sizeof(Trophy));

			STRNCPY(t->id, cJSON_GetObjectItem(node, "id")->valuestring, MAX_NAME_LENGTH);
			STRNCPY(t->title, _(cJSON_GetObjectItem(node, "title")->valuestring), MAX_DESCRIPTION_LENGTH);
			STRNCPY(t->description, _(cJSON_GetObjectItem(node, "description")->valuestring), MAX_DESCRIPTION_LENGTH);
			t->value = lookup(cJSON_GetObjectItem(node, "value")->valuestring);
			t->hidden = getJSONValue(node, "hidden", 0);
			
			t->stat = -1;
			
			/* can't use the getJSONValue here, as it could lead to false positives */
			if (cJSON_GetObjectItem(node, "stat"))
			{
				t->stat = lookup(cJSON_GetObjectItem(node, "stat")->valuestring);
				t->statValue = cJSON_GetObjectItem(node, "statValue")->valueint;
			}
			
			count[t->value]++;
			count[TROPHY_UNEARNED]++;

			tail->next = t;
			tail = t;
		}
	}
	
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Trophies (%d) [Bronze=%d, Silver=%d, Gold=%d, Platinum=%d]", count[TROPHY_UNEARNED], count[TROPHY_BRONZE], count[TROPHY_SILVER], count[TROPHY_GOLD], count[TROPHY_PLATINUM]);

	cJSON_Delete(root);
	free(text);
}