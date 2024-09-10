VALUE_PAIR *pairparsevalue(VALUE_PAIR *vp, const char *value)
{
	char		*p, *s=0;
	const char	*cp, *cs;
	int		x;
	size_t		length;
	DICT_VALUE	*dval;

	if (!value) return NULL;

	/*
	 *	Even for integers, dates and ip addresses we
	 *	keep the original string in vp->vp_strvalue.
	 */
	if (vp->type != PW_TYPE_TLV) {
		strlcpy(vp->vp_strvalue, value, sizeof(vp->vp_strvalue));
		vp->length = strlen(vp->vp_strvalue);
	}

	switch(vp->type) {
		case PW_TYPE_STRING:
			/*
			 *	Do escaping here
			 */
			p = vp->vp_strvalue;
			cp = value;
			length = 0;

			while (*cp && (length < (sizeof(vp->vp_strvalue) - 1))) {
				char c = *cp++;

				if (c == '\\') {
					switch (*cp) {
					case 'r':
						c = '\r';
						cp++;
						break;
					case 'n':
						c = '\n';
						cp++;
						break;
					case 't':
						c = '\t';
						cp++;
						break;
					case '"':
						c = '"';
						cp++;
						break;
					case '\'':
						c = '\'';
						cp++;
						break;
					case '\\':
						c = '\\';
						cp++;
						break;
					case '`':
						c = '`';
						cp++;
						break;
					case '\0':
						c = '\\'; /* no cp++ */
						break;
					default:
						if ((cp[0] >= '0') &&
						    (cp[0] <= '9') &&
						    (cp[1] >= '0') &&
						    (cp[1] <= '9') &&
						    (cp[2] >= '0') &&
						    (cp[2] <= '9') &&
						    (sscanf(cp, "%3o", &x) == 1)) {
							c = x;
							cp += 3;
						} /* else just do '\\' */
					}
				}
				*p++ = c;
				length++;
			}
			vp->vp_strvalue[length] = '\0';
			vp->length = length;
			break;

		case PW_TYPE_IPADDR:
			/*
			 *	It's a comparison, not a real IP.
			 */
			if ((vp->operator == T_OP_REG_EQ) ||
			    (vp->operator == T_OP_REG_NE)) {
				break;
			}

			/*
			 *	FIXME: complain if hostname
			 *	cannot be resolved, or resolve later!
			 */
			s = NULL;
			if ((p = strrchr(value, '+')) != NULL && !p[1]) {
				cs = s = strdup(value);
				if (!s) return NULL;
				p = strrchr(s, '+');
				*p = 0;
				vp->flags.addport = 1;
			} else {
				p = NULL;
				cs = value;
			}

			{
				fr_ipaddr_t ipaddr;

				if (ip_hton(cs, AF_INET, &ipaddr) < 0) {
					free(s);
					fr_strerror_printf("Failed to find IP address for %s", cs);
					return NULL;
				}

				vp->vp_ipaddr = ipaddr.ipaddr.ip4addr.s_addr;
			}
			free(s);
			vp->length = 4;
			break;

		case PW_TYPE_BYTE:
			vp->length = 1;

			/*
			 *	Note that ALL integers are unsigned!
			 */
			vp->vp_integer = getint(value, &p);
			if (!*p) {
				if (vp->vp_integer > 255) {
					fr_strerror_printf("Byte value \"%s\" is larger than 255", value);
					return NULL;
				}
				break;
			}
			if (check_for_whitespace(p)) break;
			goto check_for_value;

		case PW_TYPE_SHORT:
			/*
			 *	Note that ALL integers are unsigned!
			 */
			vp->vp_integer = getint(value, &p);
			vp->length = 2;
			if (!*p) {
				if (vp->vp_integer > 65535) {
					fr_strerror_printf("Byte value \"%s\" is larger than 65535", value);
					return NULL;
				}
				break;
			}
			if (check_for_whitespace(p)) break;
			goto check_for_value;

		case PW_TYPE_INTEGER:
			/*
			 *	Note that ALL integers are unsigned!
			 */
			vp->vp_integer = getint(value, &p);
			vp->length = 4;
			if (!*p) break;
			if (check_for_whitespace(p)) break;

	check_for_value:
			/*
			 *	Look for the named value for the given
			 *	attribute.
			 */
			if ((dval = dict_valbyname(vp->attribute, vp->vendor, value)) == NULL) {
				fr_strerror_printf("Unknown value %s for attribute %s",
					   value, vp->name);
				return NULL;
			}
			vp->vp_integer = dval->value;
			break;

		case PW_TYPE_DATE:
		  	{
				/*
				 *	time_t may be 64 bits, whule vp_date
				 *	MUST be 32-bits.  We need an
				 *	intermediary variable to handle
				 *	the conversions.
				 */
				time_t date;

				if (gettime(value, &date) < 0) {
					fr_strerror_printf("failed to parse time string "
						   "\"%s\"", value);
					return NULL;
				}

				vp->vp_date = date;
			}
			vp->length = 4;
			break;

		case PW_TYPE_ABINARY:
#ifdef ASCEND_BINARY
			if (strncasecmp(value, "0x", 2) == 0) {
				vp->type = PW_TYPE_OCTETS;
				goto do_octets;
			}

		  	if (ascend_parse_filter(vp) < 0 ) {
				char buffer[256];

				snprintf(buffer, sizeof(buffer), "failed to parse Ascend binary attribute: %s", fr_strerror());
				fr_strerror_printf("%s", buffer);
				return NULL;
			}
			break;

			/*
			 *	If Ascend binary is NOT defined,
			 *	then fall through to raw octets, so that
			 *	the user can at least make them by hand...
			 */
	do_octets:
#endif
			/* raw octets: 0x01020304... */
		case PW_TYPE_OCTETS:
			if (strncasecmp(value, "0x", 2) == 0) {
				size_t size;
				uint8_t *us;

				cp = value + 2;
				us = vp->vp_octets;
				vp->length = 0;

				/*
				 *	Invalid.
				 */
				size = strlen(cp);
				if ((size  & 0x01) != 0) {
					fr_strerror_printf("Hex string is not an even length string.");
					return NULL;
				}

				vp->length = size >> 1;
				if (size > 2*sizeof(vp->vp_octets)) {
					vp->type |= PW_FLAG_LONG;
					us = vp->vp_tlv = malloc(vp->length);
					if (!us) {
						fr_strerror_printf("Out of memory.");
						return NULL;
					}
				}

				if (fr_hex2bin(cp, us,
					       vp->length) != vp->length) {
					fr_strerror_printf("Invalid hex data");
					return NULL;
				}
			}
			break;

		case PW_TYPE_IFID:
			if (ifid_aton(value, (void *) &vp->vp_ifid) == NULL) {
				fr_strerror_printf("failed to parse interface-id "
					   "string \"%s\"", value);
				return NULL;
			}
			vp->length = 8;
			break;

		case PW_TYPE_IPV6ADDR:
			{
				fr_ipaddr_t ipaddr;

				if (ip_hton(value, AF_INET6, &ipaddr) < 0) {
					char buffer[1024];

					strlcpy(buffer, fr_strerror(), sizeof(buffer));

					fr_strerror_printf("failed to parse IPv6 address "
                                                           "string \"%s\": %s", value, buffer);
					return NULL;
				}
				vp->vp_ipv6addr = ipaddr.ipaddr.ip6addr;
				vp->length = 16; /* length of IPv6 address */
			}
			break;

		case PW_TYPE_IPV6PREFIX:
			p = strchr(value, '/');
			if (!p || ((p - value) >= 256)) {
				fr_strerror_printf("invalid IPv6 prefix "
					   "string \"%s\"", value);
				return NULL;
			} else {
				unsigned int prefix;
				char buffer[256], *eptr;

				memcpy(buffer, value, p - value);
				buffer[p - value] = '\0';

				if (inet_pton(AF_INET6, buffer, vp->vp_octets + 2) <= 0) {
					fr_strerror_printf("failed to parse IPv6 address "
						   "string \"%s\"", value);
					return NULL;
				}

				prefix = strtoul(p + 1, &eptr, 10);
				if ((prefix > 128) || *eptr) {
					fr_strerror_printf("failed to parse IPv6 address "
						   "string \"%s\"", value);
					return NULL;
				}
				vp->vp_octets[1] = prefix;
			}
			vp->vp_octets[0] = '\0';
			vp->length = 16 + 2;
			break;

		case PW_TYPE_ETHERNET:
			{
				const char *c1, *c2;

				length = 0;
				cp = value;
				while (*cp) {
					if (cp[1] == ':') {
						c1 = hextab;
						c2 = memchr(hextab, tolower((int) cp[0]), 16);
						cp += 2;
					} else if ((cp[1] != '\0') &&
						   ((cp[2] == ':') ||
						    (cp[2] == '\0'))) {
						   c1 = memchr(hextab, tolower((int) cp[0]), 16);
						   c2 = memchr(hextab, tolower((int) cp[1]), 16);
						   cp += 2;
						   if (*cp == ':') cp++;
					} else {
						c1 = c2 = NULL;
					}
					if (!c1 || !c2 || (length >= sizeof(vp->vp_ether))) {
						fr_strerror_printf("failed to parse Ethernet address \"%s\"", value);
						return NULL;
					}
					vp->vp_ether[length] = ((c1-hextab)<<4) + (c2-hextab);
					length++;
				}
			}
			vp->length = 6;
			break;

		case PW_TYPE_COMBO_IP:
			if (inet_pton(AF_INET6, value, vp->vp_strvalue) > 0) {
				vp->type = PW_TYPE_IPV6ADDR;
				vp->length = 16; /* length of IPv6 address */
				vp->vp_strvalue[vp->length] = '\0';

			} else {
				fr_ipaddr_t ipaddr;

				if (ip_hton(value, AF_INET, &ipaddr) < 0) {
					fr_strerror_printf("Failed to find IPv4 address for %s", value);
					return NULL;
				}

				vp->type = PW_TYPE_IPADDR;
				vp->vp_ipaddr = ipaddr.ipaddr.ip4addr.s_addr;
				vp->length = 4;
			}
			break;

		case PW_TYPE_SIGNED: /* Damned code for 1 WiMAX attribute */
			vp->vp_signed = (int32_t) strtol(value, &p, 10);
			vp->length = 4;
			break;

		case PW_TYPE_TLV: /* don't use this! */
			if (strncasecmp(value, "0x", 2) != 0) {
				fr_strerror_printf("Invalid TLV specification");
				return NULL;
			}
			length = strlen(value + 2) / 2;
			if (vp->length < length) {
				free(vp->vp_tlv);
				vp->vp_tlv = NULL;
			}
			vp->vp_tlv = malloc(length);
			if (!vp->vp_tlv) {
				fr_strerror_printf("No memory");
				return NULL;
			}
			if (fr_hex2bin(value + 2, vp->vp_tlv,
				       length) != length) {
				fr_strerror_printf("Invalid hex data in TLV");
				return NULL;
			}
			vp->length = length;
			break;

			/*
			 *  Anything else.
			 */
		default:
			fr_strerror_printf("unknown attribute type %d", vp->type);
			return NULL;
	}