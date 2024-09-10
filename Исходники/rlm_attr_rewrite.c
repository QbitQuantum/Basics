static int do_attr_rewrite(void *instance, REQUEST *request)
{
	rlm_attr_rewrite_t *data = (rlm_attr_rewrite_t *) instance;
	int ret = RLM_MODULE_NOOP;
	VALUE_PAIR *attr_vp = NULL;
	VALUE_PAIR *tmp = NULL;
	regex_t preg;
	regmatch_t pmatch[9];
	int cflags = 0;
	int err = 0;
	char done_xlat = 0;
	unsigned int len = 0;
	char err_msg[MAX_STRING_LEN];
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int counter = 0;
	char new_str[MAX_STRING_LEN];
	char *ptr, *ptr2;
	char search_STR[MAX_STRING_LEN];
	char replace_STR[MAX_STRING_LEN];

	if ((attr_vp = pairfind(request->config_items, PW_REWRITE_RULE, 0, TAG_ANY)) != NULL){
		if (data->name == NULL || strcmp(data->name,attr_vp->vp_strvalue))
			return RLM_MODULE_NOOP;
	}

	if (data->new_attr){
		/* new_attribute = yes */
		if (!radius_xlat(replace_STR, sizeof(replace_STR), data->replace, request, NULL, NULL)) {
			DEBUG2("%s: xlat on replace string failed.", data->name);
			return ret;
		}
		attr_vp = pairmake(data->attribute,replace_STR,0);
		if (attr_vp == NULL){
			DEBUG2("%s: Could not add new attribute %s with value '%s'", data->name,
				data->attribute,replace_STR);
			return ret;
		}
		switch(data->searchin){
			case RLM_REGEX_INPACKET:
				pairadd(&request->packet->vps,attr_vp);
				break;
			case RLM_REGEX_INCONFIG:
				pairadd(&request->config_items,attr_vp);
				break;
			case RLM_REGEX_INREPLY:
				pairadd(&request->reply->vps,attr_vp);
				break;
#ifdef WITH_PROXY
			case RLM_REGEX_INPROXY:
				if (!request->proxy) {
					pairbasicfree(attr_vp);
					return RLM_MODULE_NOOP;
				}
				pairadd(&request->proxy->vps, attr_vp);
				break;
			case RLM_REGEX_INPROXYREPLY:
				if (!request->proxy_reply) {
					pairbasicfree(attr_vp);
					return RLM_MODULE_NOOP;
				}
				pairadd(&request->proxy_reply->vps, attr_vp);
				break;
#endif
			default:
				radlog(L_ERR, "%s: Illegal value for searchin. Changing to packet.", data->name);
				data->searchin = RLM_REGEX_INPACKET;
				pairadd(&request->packet->vps,attr_vp);
				break;
		}
		DEBUG2("%s: Added attribute %s with value '%s'", data->name,data->attribute,replace_STR);
		ret = RLM_MODULE_OK;
	} else {
		int replace_len = 0;

		/* new_attribute = no */
		switch (data->searchin) {
			case RLM_REGEX_INPACKET:
				if (!data->da->vendor && (data->da->attr == PW_USER_NAME))
					attr_vp = request->username;
				else if (!data->da->vendor && (data->da->attr == PW_USER_PASSWORD))
					attr_vp = request->password;
				else
					tmp = request->packet->vps;
				break;
			case RLM_REGEX_INCONFIG:
				tmp = request->config_items;
				break;
			case RLM_REGEX_INREPLY:
				tmp = request->reply->vps;
				break;
#ifdef WITH_PROXY
			case RLM_REGEX_INPROXYREPLY:
				if (!request->proxy_reply)
					return RLM_MODULE_NOOP;
				tmp = request->proxy_reply->vps;
				break;
			case RLM_REGEX_INPROXY:
				if (!request->proxy)
					return RLM_MODULE_NOOP;
				tmp = request->proxy->vps;
				break;
#endif
			default:
				radlog(L_ERR, "%s: Illegal value for searchin. Changing to packet.", data->name);
				data->searchin = RLM_REGEX_INPACKET;
				attr_vp = pairfind(request->packet->vps, data->da->attr, data->da->vendor, TAG_ANY);
				break;
		}
do_again:
		if (tmp != NULL)
			attr_vp = pairfind(tmp, data->da->attr, data->da->vendor, TAG_ANY);
		if (attr_vp == NULL) {
			DEBUG2("%s: Could not find value pair for attribute %s", data->name,data->attribute);
			return ret;
		}
		if (attr_vp->vp_strvalue == NULL || attr_vp->length == 0){
			DEBUG2("%s: Attribute %s string value NULL or of zero length", data->name,data->attribute);
			return ret;
		}
		cflags |= REG_EXTENDED;
		if (data->nocase)
			cflags |= REG_ICASE;

		if (!radius_xlat(search_STR, sizeof(search_STR), data->search, request, NULL, NULL) && data->search_len != 0) {
			DEBUG2("%s: xlat on search string failed.", data->name);
			return ret;
		}

		if ((err = regcomp(&preg,search_STR,cflags))) {
			regerror(err, &preg, err_msg, MAX_STRING_LEN);
			DEBUG2("%s: regcomp() returned error: %s", data->name,err_msg);
			return ret;
		}

		if ((attr_vp->type == PW_TYPE_IPADDR) &&
		    (attr_vp->vp_strvalue[0] == '\0')) {
			inet_ntop(AF_INET, &(attr_vp->vp_ipaddr),
				  attr_vp->vp_strvalue,
				  sizeof(attr_vp->vp_strvalue));
		}

		ptr = new_str;
		ptr2 = attr_vp->vp_strvalue;
		counter = 0;

		for ( i = 0 ;i < (unsigned)data->num_matches; i++) {
			err = regexec(&preg, ptr2, REQUEST_MAX_REGEX, pmatch, 0);
			if (err == REG_NOMATCH) {
				if (i == 0) {
					DEBUG2("%s: Does not match: %s = %s", data->name,
							data->attribute, attr_vp->vp_strvalue);
					regfree(&preg);
					goto to_do_again;
				} else
					break;
			}
			if (err != 0) {
				regfree(&preg);
				radlog(L_ERR, "%s: match failure for attribute %s with value '%s'", data->name,
						data->attribute, attr_vp->vp_strvalue);
				return ret;
			}
			if (pmatch[0].rm_so == -1)
				break;
			len = pmatch[0].rm_so;
			if (data->append) {
				len = len + (pmatch[0].rm_eo - pmatch[0].rm_so);
			}
			counter += len;
			if (counter >= MAX_STRING_LEN) {
				regfree(&preg);
				DEBUG2("%s: Replacement out of limits for attribute %s with value '%s'", data->name,
						data->attribute, attr_vp->vp_strvalue);
				return ret;
			}

			memcpy(ptr, ptr2,len);
			ptr += len;
			*ptr = '\0';
			ptr2 += pmatch[0].rm_eo;

			if (i == 0){
				/*
				 * We only run on the first match, sorry
				 */
				for(j = 0; j <= REQUEST_MAX_REGEX; j++){
					char *p;
					char buffer[sizeof(attr_vp->vp_strvalue)];

					/*
				   	 * Stolen from src/main/valuepair.c, paircompare()
				 	 */

					/*
					 * Delete old matches if the corresponding match does not
					 * exist in the current regex
					 */
					if (pmatch[j].rm_so == -1){
						p = request_data_get(request,request,REQUEST_DATA_REGEX | j);
						if (p){
							free(p);
							continue;
						}
						break;
					}
					memcpy(buffer,
					       attr_vp->vp_strvalue + pmatch[j].rm_so,
					       pmatch[j].rm_eo - pmatch[j].rm_so);
					buffer[pmatch[j].rm_eo - pmatch[j].rm_so] = '\0';
					p = strdup(buffer);
					request_data_add(request,request,REQUEST_DATA_REGEX | j,p,free);
				}
			}

			if (!done_xlat){
				if (data->replace_len != 0 &&
				radius_xlat(replace_STR, sizeof(replace_STR), data->replace, request, NULL, NULL) == 0) {
					DEBUG2("%s: xlat on replace string failed.", data->name);
					return ret;
				}
				replace_len = (data->replace_len != 0) ? strlen(replace_STR) : 0;
				done_xlat = 1;
			}

			counter += replace_len;
			if (counter >= MAX_STRING_LEN) {
				regfree(&preg);
				DEBUG2("%s: Replacement out of limits for attribute %s with value '%s'", data->name,
						data->attribute, attr_vp->vp_strvalue);
				return ret;
			}
			if (replace_len){
				memcpy(ptr, replace_STR, replace_len);
				ptr += replace_len;
				*ptr = '\0';
			}
		}
		regfree(&preg);
		len = strlen(ptr2) + 1;		/* We add the ending NULL */
		counter += len;
		if (counter >= MAX_STRING_LEN){
			DEBUG2("%s: Replacement out of limits for attribute %s with value '%s'", data->name,
					data->attribute, attr_vp->vp_strvalue);
			return ret;
		}
		memcpy(ptr, ptr2, len);
		ptr[len] = '\0';

		DEBUG2("%s: Changed value for attribute %s from '%s' to '%s'", data->name,
				data->attribute, attr_vp->vp_strvalue, new_str);
		if (pairparsevalue(attr_vp, new_str) == NULL) {
			DEBUG2("%s: Could not write value '%s' into attribute %s: %s", data->name, new_str, data->attribute, fr_strerror());
			return ret;
		}

to_do_again:
		ret = RLM_MODULE_OK;

		if (tmp != NULL){
			tmp = attr_vp->next;
			if (tmp != NULL)
				goto do_again;
		}
	}

	return ret;
}