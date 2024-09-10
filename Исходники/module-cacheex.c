//Format:
//caid:prov:srvid:pid:chid:ecmlen=caid:prov:srvid:pid:chid:ecmlen[,validfrom,validto]
//validfrom: default=-2000
//validto: default=4000
//valid time if found in cache
static struct s_cacheex_matcher *cacheex_matcher_read_int(void)
{
	FILE *fp = open_config_file(cs_cacheex_matcher);
	if(!fp)
		{ return NULL; }

	char token[1024];
	uint8_t type;
	int32_t i, ret, count = 0;
	struct s_cacheex_matcher *new_cacheex_matcher = NULL, *entry, *last = NULL;
	uint32_t line = 0;

	while(fgets(token, sizeof(token), fp))
	{
		line++;
		if(strlen(token) <= 1) { continue; }
		if(token[0] == '#' || token[0] == '/') { continue; }
		if(strlen(token) > 100) { continue; }

		for(i = 0; i < (int)strlen(token); i++)
		{
			if((token[i] == ':' || token[i] == ' ') && token[i + 1] == ':')
			{
				memmove(token + i + 2, token + i + 1, strlen(token) - i + 1);
				token[i + 1] = '0';
			}
			if(token[i] == '#' || token[i] == '/')
			{
				token[i] = '\0';
				break;
			}
		}

		type = 'm';
		uint32_t caid = 0, provid = 0, srvid = 0, pid = 0, chid = 0, ecmlen = 0;
		uint32_t to_caid = 0, to_provid = 0, to_srvid = 0, to_pid = 0, to_chid = 0, to_ecmlen = 0;
		int32_t valid_from = -2000, valid_to = 4000;

		ret = sscanf(token, "%c:%4x:%6x:%4x:%4x:%4x:%4X=%4x:%6x:%4x:%4x:%4x:%4X,%4d,%4d",
					 &type,
					 &caid, &provid, &srvid, &pid, &chid, &ecmlen,
					 &to_caid, &to_provid, &to_srvid, &to_pid, &to_chid, &to_ecmlen,
					 &valid_from, &valid_to);

		type = tolower(type);

		if(ret < 7 || type != 'm')
			{ continue; }

		if(!cs_malloc(&entry, sizeof(struct s_cacheex_matcher)))
		{
			fclose(fp);
			return new_cacheex_matcher;
		}
		count++;
		entry->line = line;
		entry->type = type;
		entry->caid = caid;
		entry->provid = provid;
		entry->srvid = srvid;
		entry->pid = pid;
		entry->chid = chid;
		entry->ecmlen = ecmlen;
		entry->to_caid = to_caid;
		entry->to_provid = to_provid;
		entry->to_srvid = to_srvid;
		entry->to_pid = to_pid;
		entry->to_chid = to_chid;
		entry->to_ecmlen = to_ecmlen;
		entry->valid_from = valid_from;
		entry->valid_to = valid_to;

		cs_log_dbg(D_TRACE, "cacheex-matcher: %c: %04X@%06X:%04X:%04X:%04X:%02X = %04X@%06X:%04X:%04X:%04X:%02X valid %d/%d",
					entry->type, entry->caid, entry->provid, entry->srvid, entry->pid, entry->chid, entry->ecmlen,
					entry->to_caid, entry->to_provid, entry->to_srvid, entry->to_pid, entry->to_chid, entry->to_ecmlen,
					entry->valid_from, entry->valid_to);

		if(!new_cacheex_matcher)
		{
			new_cacheex_matcher = entry;
			last = new_cacheex_matcher;
		}
		else
		{
			last->next = entry;
			last = entry;
		}
	}

	if(count)
		{ cs_log("%d entries read from %s", count, cs_cacheex_matcher); }

	fclose(fp);

	return new_cacheex_matcher;
}