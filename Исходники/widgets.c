static void loadWidgetSet(char *filename)
{
	cJSON *root, *node;
	char *text;
	Widget *w;
	
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	text = readFile(filename);
	root = cJSON_Parse(text);

	for (node = root->child ; node != NULL ; node = node->next)
	{
		w = malloc(sizeof(Widget));
		memset(w, 0, sizeof(Widget));
		
		w->type = lookup(cJSON_GetObjectItem(node, "type")->valuestring);
		STRNCPY(w->name, cJSON_GetObjectItem(node, "name")->valuestring, MAX_NAME_LENGTH);
		STRNCPY(w->group, cJSON_GetObjectItem(node, "group")->valuestring, MAX_NAME_LENGTH);
		w->rect.x = cJSON_GetObjectItem(node, "x")->valueint;
		w->rect.y = cJSON_GetObjectItem(node, "y")->valueint;
		w->rect.w = cJSON_GetObjectItem(node, "w")->valueint;
		w->rect.h = cJSON_GetObjectItem(node, "h")->valueint;
		w->enabled = 1;
		w->visible = 1;
		
		if (w->rect.x == -1)
		{
			w->rect.x = SCREEN_WIDTH / 2;
		}
		
		switch (w->type)
		{
			case WT_BUTTON:
				STRNCPY(w->text, cJSON_GetObjectItem(node, "text")->valuestring, MAX_NAME_LENGTH);
				w->rect.x -= w->rect.w / 2;
				w->rect.y -= (w->rect.h / 2) + 8;
				break;
				
			case WT_SELECT:
				STRNCPY(w->text, cJSON_GetObjectItem(node, "text")->valuestring, MAX_NAME_LENGTH);
				w->rect.x -= w->rect.w / 2;
				w->rect.y -= (w->rect.h / 2) + 8;
				createOptions(w, cJSON_GetObjectItem(node, "options")->valuestring);
				break;
		}
	
		tail->next = w;
		tail = w;
	}

	cJSON_Delete(root);
	free(text);
}