/**
 * Convert human-readable version of a 'value' of a record to the binary
 * representation.
 *
 * @param type type of the record
 * @param s human-readable string
 * @param data set to value in binary encoding (will be allocated)
 * @param data_size set to number of bytes in data
 * @return GNUNET_OK on success
 */
int
GNUNET_NAMESTORE_string_to_value (uint32_t type,
				  const char *s,
				  void **data,
				  size_t *data_size)
{
  struct in_addr value_a;
  struct in6_addr value_aaaa;
  struct GNUNET_CRYPTO_ShortHashCode pkey;
  struct soa_data *soa;
  struct vpn_data *vpn;
  struct tlsa_data *tlsa;
  char result[253 + 1];
  char soa_rname[253 + 1];
  char soa_mname[253 + 1];
  char s_peer[103 + 1];
  char s_serv[253 + 1];
  unsigned int soa_serial;
  unsigned int soa_refresh;
  unsigned int soa_retry;
  unsigned int soa_expire;
  unsigned int soa_min;
  uint16_t mx_pref;
  uint16_t mx_pref_n;
  unsigned int proto;
  
  switch (type)
  {
  case 0:
    GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
		_("Unsupported record type %d\n"),
		(int) type);
    return GNUNET_SYSERR;
  case GNUNET_DNSPARSER_TYPE_A:
    if (1 != inet_pton (AF_INET, s, &value_a))
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  _("Unable to parse IPv4 address `%s'\n"),
		  s);
      return GNUNET_SYSERR;
    }
    *data = GNUNET_malloc (sizeof (struct in_addr));
    memcpy (*data, &value_a, sizeof (value_a));
    *data_size = sizeof (value_a);
    return GNUNET_OK;
  case GNUNET_DNSPARSER_TYPE_NS:
    *data = GNUNET_strdup (s);
    *data_size = strlen (s) + 1;
    return GNUNET_OK;
  case GNUNET_DNSPARSER_TYPE_CNAME:
    *data = GNUNET_strdup (s);
    *data_size = strlen (s) + 1;
    return GNUNET_OK;
  case GNUNET_DNSPARSER_TYPE_SOA:
    if (7 != SSCANF (s, 
		     "rname=%253s mname=%253s %u,%u,%u,%u,%u",
		     soa_rname, soa_mname,
		     &soa_serial, &soa_refresh, &soa_retry, &soa_expire, &soa_min))
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  _("Unable to parse SOA record `%s'\n"),
		  s);
      return GNUNET_SYSERR;
    }
    *data_size = sizeof (struct soa_data)+strlen(soa_rname)+strlen(soa_mname)+2;
    *data = GNUNET_malloc (*data_size);
    soa = (struct soa_data*)*data;
    soa->serial = htonl(soa_serial);
    soa->refresh = htonl(soa_refresh);
    soa->retry = htonl(soa_retry);
    soa->expire = htonl(soa_expire);
    soa->minimum = htonl(soa_min);
    strcpy((char*)&soa[1], soa_rname);
    strcpy((char*)&soa[1]+strlen(*data)+1, soa_mname);
    return GNUNET_OK;
  case GNUNET_DNSPARSER_TYPE_PTR:
    *data = GNUNET_strdup (s);
    *data_size = strlen (s);
    return GNUNET_OK;
  case GNUNET_DNSPARSER_TYPE_MX:
    if (2 != SSCANF(s, "%hu,%253s", &mx_pref, result))
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  _("Unable to parse MX record `%s'\n"),
		  s);
      return GNUNET_SYSERR;
    }
    *data_size = sizeof (uint16_t)+strlen(result)+1;
    *data = GNUNET_malloc (*data_size);
    mx_pref_n = htons(mx_pref);
    memcpy(*data, &mx_pref_n, sizeof (uint16_t));
    strcpy((*data)+sizeof (uint16_t), result);
    return GNUNET_OK;
  case GNUNET_DNSPARSER_TYPE_TXT:
    *data = GNUNET_strdup (s);
    *data_size = strlen (s);
    return GNUNET_OK;
  case GNUNET_DNSPARSER_TYPE_AAAA:
    if (1 != inet_pton (AF_INET6, s, &value_aaaa))    
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  _("Unable to parse IPv6 address `%s'\n"),
		  s);
      return GNUNET_SYSERR;
    }
    *data = GNUNET_malloc (sizeof (struct in6_addr));
    *data_size = sizeof (struct in6_addr);
    memcpy (*data, &value_aaaa, sizeof (value_aaaa));
    return GNUNET_OK;
  case GNUNET_NAMESTORE_TYPE_PKEY:
    if (GNUNET_OK !=
	GNUNET_CRYPTO_short_hash_from_string (s, &pkey))
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  _("Unable to parse PKEY record `%s'\n"),
		  s);
      return GNUNET_SYSERR;
    }
    *data = GNUNET_malloc (sizeof (struct GNUNET_CRYPTO_ShortHashCode));
    memcpy (*data, &pkey, sizeof (pkey));
    *data_size = sizeof (struct GNUNET_CRYPTO_ShortHashCode);
    return GNUNET_OK;
  case GNUNET_NAMESTORE_TYPE_PSEU:
    *data = GNUNET_strdup (s);
    *data_size = strlen (s);
    return GNUNET_OK;
  case GNUNET_NAMESTORE_TYPE_LEHO:
    *data = GNUNET_strdup (s);
    *data_size = strlen (s);
    return GNUNET_OK;
  case GNUNET_NAMESTORE_TYPE_VPN:
    if (3 != SSCANF (s,"%u %103s %253s",
		     &proto, s_peer, s_serv))
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  _("Unable to parse VPN record string `%s'\n"),
		  s);
      return GNUNET_SYSERR;
    }
    *data_size = sizeof (struct vpn_data) + strlen (s_serv) + 1;
    *data = vpn = GNUNET_malloc (*data_size);
    if (GNUNET_OK != GNUNET_CRYPTO_hash_from_string ((char*)&s_peer,
						     &vpn->peer))
    {
      GNUNET_free (vpn);
      *data_size = 0;
      return GNUNET_SYSERR;
    }
    vpn->proto = htons ((uint16_t) proto);
    strcpy ((char*)&vpn[1], s_serv);
    return GNUNET_OK;
  case GNUNET_DNSPARSER_TYPE_TLSA:
    *data_size = sizeof (struct tlsa_data) + strlen (s) - 6;
    *data = tlsa = GNUNET_malloc (*data_size);
    if (4 != SSCANF (s, "%c %c %c %s",
		     &tlsa->usage,
		     &tlsa->selector,
		     &tlsa->matching_type,
		     (char*)&tlsa[1]))
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  _("Unable to parse TLSA record string `%s'\n"), 
		  s);
      *data_size = 0;
      GNUNET_free (tlsa);
      return GNUNET_SYSERR;
    }
    return GNUNET_OK;
  default:
    GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
		_("Unsupported record type %d\n"),
		(int) type);
    return GNUNET_SYSERR;
  }
}