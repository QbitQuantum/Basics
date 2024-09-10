/* information are parsed but not all are used in our case, ie. for xenstat */
int parseNetDevLine(char *line, char *iface, unsigned long long *rxBytes, unsigned long long *rxPackets,
		unsigned long long *rxErrs, unsigned long long *rxDrops, unsigned long long *rxFifo,
		unsigned long long *rxFrames, unsigned long long *rxComp, unsigned long long *rxMcast,
		unsigned long long *txBytes, unsigned long long *txPackets, unsigned long long *txErrs,
		unsigned long long *txDrops, unsigned long long *txFifo, unsigned long long *txColls,
		unsigned long long *txCarrier, unsigned long long *txComp)
{
	/* Temporary/helper variables */
	int ret;
	char *tmp;
	int i = 0, x = 0, col = 0;
	regex_t r;
	regmatch_t matches[19];
	int num = 19;

	/* Regular exception to parse all the information from /proc/net/dev line */
	char *regex = "([^:]*):([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)"
			"[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*"
			"([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)[ ]*([^ ]*)";

	/* Initialize all variables called has passed as non-NULL to zeros */
	if (iface != NULL)
		memset(iface, 0, sizeof(*iface));
	if (rxBytes != NULL)
		*rxBytes = 0;
	if (rxPackets != NULL)
		*rxPackets = 0;
	if (rxErrs != NULL)
		*rxErrs = 0;
	if (rxDrops != NULL)
		*rxDrops = 0;
	if (rxFifo != NULL)
		*rxFifo = 0;
	if (rxFrames != NULL)
		*rxFrames = 0;
	if (rxPackets != NULL)
		*rxPackets = 0;
	if (rxComp != NULL)
		*rxComp = 0;
	if (txBytes != NULL)
		*txBytes = 0;
	if (txPackets != NULL)
		*txPackets = 0;
	if (txErrs != NULL)
		*txErrs = 0;
	if (txDrops != NULL)
		*txDrops = 0;
	if (txFifo != NULL)
		*txFifo = 0;
	if (txColls != NULL)
		*txColls = 0;
	if (txCarrier != NULL)
		*txCarrier = 0;
	if (txComp != NULL)
		*txComp = 0;

	if ((ret = regcomp(&r, regex, REG_EXTENDED))) {
		regfree(&r);
		return ret;
	}

	tmp = (char *)malloc( sizeof(char) );
	if (regexec (&r, line, num, matches, REG_EXTENDED) == 0){
		for (i = 1; i < num; i++) {
			/* The expression matches are empty sometimes so we need to check it first */
			if (matches[i].rm_eo - matches[i].rm_so > 0) {
				/* Col variable contains current id of non-empty match */
				col++;
				tmp = (char *)realloc(tmp, (matches[i].rm_eo - 
							matches[i].rm_so + 1) * sizeof(char));
				for (x = matches[i].rm_so; x < matches[i].rm_eo; x++)
					tmp[x - matches[i].rm_so] = line[x];

				/* We populate all the fields from /proc/net/dev line */
				if (i > 1) {
					unsigned long long ullTmp = strtoull(tmp, NULL, 10);

					switch (col) {
						case 2: if (rxBytes != NULL)
								*rxBytes = ullTmp;
							break;
						case 3: if (rxPackets != NULL)
								*rxPackets = ullTmp;
							break;
						case 4: if (rxErrs != NULL)
								*rxErrs = ullTmp;
							break;
						case 5: if (rxDrops != NULL)
								*rxDrops = ullTmp;
							break;
						case 6: if (rxFifo != NULL)
								*rxFifo = ullTmp;
							break;
						case 7: if (rxFrames != NULL)
								*rxFrames = ullTmp;
							break;
						case 8: if (rxComp != NULL)
								*rxComp = ullTmp;
							break;
						case 9: if (rxMcast != NULL)
								*rxMcast = ullTmp;
							break;
						case 10: if (txBytes != NULL)
								*txBytes = ullTmp;
							break;
						case 11: if (txPackets != NULL)
								*txPackets = ullTmp;
							break;
						case 12: if (txErrs != NULL)
								*txErrs = ullTmp;
							break;
						case 13: if (txDrops != NULL)
								*txDrops = ullTmp;
							break;
						case 14: if (txFifo != NULL)
								*txFifo = ullTmp;
							break;
						case 15: if (txColls != NULL)
								*txColls = ullTmp;
							break;
						case 16: if (txCarrier != NULL)
								*txCarrier = ullTmp;
							break;
						case 17: if (txComp != NULL)
								*txComp = ullTmp;
							break;
					}
				}
				else
				/* There were errors when parsing this directly in RE. strpbrk() helps */
				if (iface != NULL) {
					char *tmp2 = strpbrk(tmp, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
					if (tmp2 != NULL)
						strcpy(iface, tmp2);
				}

				memset(tmp, 0, matches[i].rm_eo - matches[i].rm_so);
			}
		}
	}

	free(tmp);
	regfree(&r);

	return 0;
}