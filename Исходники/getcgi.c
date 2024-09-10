accept_languages * parse_accept_languages(char * acceptlang) {
	char *	langdup;	/* Duplicate of accept language for parsing */
	accept_languages	*langs = NULL;
	char *	langtok;	/* Language token (language + locality + q value) */
	char *	saveptr;	/* Save state of tokenization */
	char *	qdelim;		/* location of the delimiter ';q=' */
	char *	localitydelim;	/* Delimiter for locality specifier */
	int		x;
	char *	stp;

	/* If the browser did not pass an HTTP_ACCEPT_LANGUAGE variable, there
		is not much we can do */
	if(NULL == acceptlang) {
		return NULL;
		}

	/* Duplicate the browser supplied HTTP_ACCEPT_LANGUAGE variable */
	if(NULL == (langdup = strdup(acceptlang))) {
		printf("Unable to allocate memory for langdup\n");
		return NULL;
		}

	/* Initialize the structure to contain the parsed HTTP_ACCEPT_LANGUAGE
		information */
	if(NULL == (langs = malloc(sizeof(accept_languages)))) {
		printf("Unable to allocate memory for langs\n");
		free(langdup);
		return NULL;
		}
	langs->count = 0;
	langs->languages = (accept_language **)NULL;

	/* Tokenize the HTTP_ACCEPT_LANGUAGE string */
	langtok = strtok_r(langdup, ",", &saveptr);
	while(langtok != NULL) {
		/* Bump the count and allocate memory for structures */
		langs->count++;
		if(NULL == langs->languages) {
			/* Adding first language */
			if(NULL == (langs->languages =
			                malloc(langs->count * sizeof(accept_language *)))) {
				printf("Unable to allocate memory for first language\n");
				langs->count--;
				free_accept_languages(langs);
				free(langdup);
				return NULL;
				}
			}
		else {
			/* Adding additional language */
			if(NULL == (langs->languages = realloc(langs->languages,
			                                       langs->count * sizeof(accept_language *)))) {
				printf("Unable to allocate memory for additional language\n");
				langs->count--;
				free_accept_languages(langs);
				free(langdup);
				return NULL;
				}
			}
		if(NULL == (langs->languages[ langs->count - 1] =
		                malloc(sizeof(accept_language)))) {
			printf("Unable to allocate memory for language\n");
			langs->count--;
			free_accept_languages(langs);
			free(langdup);
			return NULL;
			}
		langs->languages[ langs->count - 1]->language = (char *)NULL;
		langs->languages[ langs->count - 1]->locality = (char *)NULL;
		langs->languages[ langs->count - 1]->q = 1.0;

		/* Check to see if there is a q value */
		qdelim = strstr(langtok, ACCEPT_LANGUAGE_Q_DELIMITER);

		if(NULL != qdelim) {	/* found a q value */
			langs->languages[ langs->count - 1]->q =
			    strtod(qdelim + strlen(ACCEPT_LANGUAGE_Q_DELIMITER), NULL);
			langtok[ qdelim - langtok] = '\0';
			}

		/* Check to see if there is a locality specifier */
		if(NULL == (localitydelim = strchr(langtok, '-'))) {
			localitydelim = strchr(langtok, '_');
			}

		if(NULL != localitydelim) {
			/* We have a locality delimiter, so copy it */
			if(NULL == (langs->languages[ langs->count - 1]->locality =
			                strdup(localitydelim + 1))) {
				printf("Unable to allocate memory for locality '%s'\n",
				       langtok);
				free_accept_languages(langs);
				free(langdup);
				return NULL;
				}

			/* Ensure it is upper case */
			for(x = 0, stp = langs->languages[ langs->count - 1]->locality;
			        x < strlen(langs->languages[ langs->count - 1]->locality);
			        x++, stp++) {
				*stp = toupper(*stp);
				}

			/* Then null out the delimiter so the language copy works */
			*localitydelim = '\0';
			}
		if(NULL == (langs->languages[ langs->count - 1]->language =
		                strdup(langtok))) {
			printf("Unable to allocate memory for language '%s'\n",
			       langtok);
			free_accept_languages(langs);
			free(langdup);
			return NULL;
			}

		/* Get the next language token */
		langtok = strtok_r(NULL, ",", &saveptr);
		}

	free(langdup);
	return langs;
	}