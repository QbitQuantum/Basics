static void loadCapitalShipDef(char *filename)
{
	cJSON *root;
	char *text;
	Entity *e;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	text = readFile(filename);

	root = cJSON_Parse(text);

	if (root)
	{
		e = malloc(sizeof(Entity));
		memset(e, 0, sizeof(Entity));
		defTail->next = e;
		defTail = e;

		e->type = ET_CAPITAL_SHIP;
		e->active = 1;

		STRNCPY(e->name, cJSON_GetObjectItem(root, "name")->valuestring, MAX_NAME_LENGTH);
		STRNCPY(e->defName, e->name, MAX_NAME_LENGTH);
		e->shield = e->maxShield = cJSON_GetObjectItem(root, "shield")->valueint;
		e->shieldRechargeRate = cJSON_GetObjectItem(root, "shieldRechargeRate")->valueint;
		e->texture = getTexture(cJSON_GetObjectItem(root, "texture")->valuestring);
		e->speed = 1;
		e->systemPower = 3;
		e->flags = EF_NO_HEALTH_BAR;

		e->action = think;
		e->die = die;

		SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

		e->separationRadius = MAX(e->w, e->h);

		loadComponents(e, cJSON_GetObjectItem(root, "components"));

		loadGuns(e, cJSON_GetObjectItem(root, "guns"));

		loadEngines(e, cJSON_GetObjectItem(root, "engines"));

		cJSON_Delete(root);
	}
	else
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Failed to load '%s'", filename);
	}

	free(text);
}