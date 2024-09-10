void mavlink_parseParams1 (xmlDocPtr doc, xmlNodePtr cur, char *name) { 
	int n = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	char tmp_str3[1024];
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[n].name, name) == 0) {
			break;
		}
	}
	if (n == MAVLINK_PARAMETER_MAX) {
		return;
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Range"))) {
			float min = 0.0;
			float max = 0.0;
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				sscanf((char *)key, "%f %f", &min, &max);
				MavLinkVars[n].min = min;
				MavLinkVars[n].max = max;
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Description"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].desc, (char *)key, 1023);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Group"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].group, (char *)key, 20);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Values"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].values, (char *)key, 1023);
				if (MavLinkVars[n].values[0] != 0) {
					MavLinkVars[n].min = atof(MavLinkVars[n].values);
					for (n2 = 0; n2 < strlen(MavLinkVars[n].values); n2++) {
						if (MavLinkVars[n].values[n2] == ',') {
							strncpy(tmp_str3, MavLinkVars[n].values + n3, 1023);
							for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
								if (tmp_str3[n4] == ',') {
									tmp_str3[n4] = 0;
									break;
								}
							}
							n3 = n2 + 1;
						}
					}
					strncpy(tmp_str3, MavLinkVars[n].values + n3, 1023);
					MavLinkVars[n].max = atof(tmp_str3);
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Bits"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].bits, (char *)key, 1023);
				if (MavLinkVars[n].bits[0] != 0) {
					MavLinkVars[n].min = 0;
					for (n2 = 0; n2 < strlen(MavLinkVars[n].bits); n2++) {
						if (MavLinkVars[n].bits[n2] == ',') {
							strncpy(tmp_str3, MavLinkVars[n].bits + n3, 1023);
							for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
								if (tmp_str3[n4] == ',') {
									tmp_str3[n4] = 0;
									break;
								}
							}
							n3 = n2 + 1;
						}
					}
					strncpy(tmp_str3, MavLinkVars[n].bits + n3, 1023);
					MavLinkVars[n].max = (float)((1<<atoi(tmp_str3)) * (1<<atoi(tmp_str3)) - 1);
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"DisplayName"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].display, (char *)key, 100);
				xmlFree(key);
			}
		}
		cur = cur->next;
	}
	return;
}