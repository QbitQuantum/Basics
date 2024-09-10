static inline int oma_match_external_list_condition(xmlNodePtr condition, subs_t *subs, str *w_uri)
{
        int found = 0;
        str anchor, uri;
        str *normalized_uri;
	struct sip_uri sip_uri;
        xcap_uri_t anchor_uri;
        xmlNodePtr entry_node = NULL;
        xmlNodePtr rl_node = NULL, rl_entry = NULL;
        xmlDocPtr rl_doc = NULL;

        if(!integrated_xcap_server)
        {
	        LM_ERR("<external-list> is not supported in non integrated mode\n");
	        return 0;
        }

        if(parse_uri(subs->pres_uri.s, subs->pres_uri.len, &sip_uri) < 0)
        {
                LM_ERR("failed to parse uri\n");
                return 0;
        }

	for(entry_node = condition->children; entry_node; entry_node = entry_node->next)
	{
		if(xmlStrcasecmp(entry_node->name, (unsigned char*)"entry") != 0)
		        continue;

		rl_node = NULL;
		rl_doc = NULL;
		anchor.s = NULL;
		uri.s = NULL;

                anchor.s = xmlNodeGetAttrContentByName(entry_node, "anc");
                if(anchor.s == NULL)
                {
                        LM_ERR("cannot get external-list entry anchor\n");
                        continue;
                }
                anchor.len = strlen(anchor.s);
		if(xcapParseUri(&anchor, &anchor_uri) != 0)
                {
		        LM_ERR("unable to parse URI for external-list entry anchor\n");
			xmlFree(anchor.s);
			continue;
                }
		xmlFree(anchor.s);
                /* TODO: validate XUI? */
		if(get_resource_list(&sip_uri.user, &sip_uri.host, &anchor_uri.filename, &anchor_uri.selector, &rl_node, &rl_doc) < 0)
                {
		        LM_ERR("error getting resource-list list pointed by external list anchor\n");
			continue;
                }
                for(rl_entry = rl_node->children; rl_entry; rl_entry = rl_entry->next)
                {
                        if(xmlStrcasecmp(rl_entry->name, (unsigned char*)"entry") != 0)
                                continue;
			uri.s = xmlNodeGetAttrContentByName(rl_entry, "uri");
			if(uri.s == NULL)
			{
				LM_ERR("when extracting entry uri attribute\n");
				continue;
			}
                        uri.len = strlen(uri.s);

                        normalized_uri = normalizeSipUri(&uri);
                        if (normalized_uri->s == NULL || normalized_uri->len == 0)
                        {
                                LM_ERR("normalizing URI\n");
                                xmlFree(uri.s);
                                continue;
                        }
                        xmlFree(uri.s);

                        if (normalized_uri->len == w_uri->len && strncmp(normalized_uri->s, w_uri->s, w_uri->len) == 0)
                        {
                                found = 1;
                                break;
                        }
                }
		xmlFreeDoc(rl_doc);
                if (found)
                        break;
	}

	return found;

}