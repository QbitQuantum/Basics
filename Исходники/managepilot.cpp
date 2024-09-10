//Generates a list of available campaigns. Sets active campaign to "freespace2.fc2", or if that is unavailable, the first campaign found
void pilot_set_start_campaign(player* p)
{
	char wild_card[10];
	int i, j, incr = 0;
	char *t = NULL;
	int rc = 0;
	char *campaign_file_list[MAX_CAMPAIGNS];

	memset(wild_card, 0, sizeof(wild_card));
	strcpy_s(wild_card, NOX("*"));
	strcat_s(wild_card, FS_CAMPAIGN_FILE_EXT);

	// set filter for cf_get_file_list() if there isn't one set already (the simroom has a special one)
	if (Get_file_list_filter == NULL)
		Get_file_list_filter = campaign_file_list_filter;

	// now get the list of all campaign names
	// NOTE: we don't do sorting here, but we assume CF_SORT_NAME, and do it manually below
	rc = cf_get_file_list(MAX_CAMPAIGNS, campaign_file_list, CF_TYPE_MISSIONS, wild_card, CF_SORT_NONE);

	for (i = 0; i < rc; i++) 
	{
		if (!stricmp(campaign_file_list[i], Default_campaign_file_name))
		{
			strcpy_s(p->current_campaign, campaign_file_list[i]);
			return;
		}
	}

	// now sort everything
	incr = local_num_campaigns / 2;

	while (incr > 0) {
		for (i = incr; i < local_num_campaigns; i++) {
			j = i - incr;
	
			while (j >= 0) {
				char *name1 = Campaign_names[j];
				char *name2 = Campaign_names[j + incr];

				// if we hit this then a coder probably did something dumb (like not needing to sort)
				if ( (name1 == NULL) || (name2 == NULL) ) {
					Int3();
					break;
				}

				if ( !strnicmp(name1, "the ", 4) )
					name1 += 4;

				if ( !strnicmp(name2, "the ", 4) )
					name2 += 4;

				if (stricmp(name1, name2) > 0) {
					// first, do filenames
					t = campaign_file_list[j];
					campaign_file_list[j] = campaign_file_list[j + incr];
					campaign_file_list[j + incr] = t;

					j -= incr;
				} else {
					break;
				}
			}
		}

		incr /= 2;
	}

	if (rc > 0)
		strcpy_s(p->current_campaign, campaign_file_list[0]);
	else
		strcpy_s(p->current_campaign, "<none>");

}