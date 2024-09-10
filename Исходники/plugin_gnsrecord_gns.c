/**
 * Convert human-readable version of a 'value' of a record to the binary
 * representation.
 *
 * @param cls closure, unused
 * @param type type of the record
 * @param s human-readable string
 * @param data set to value in binary encoding (will be allocated)
 * @param data_size set to number of bytes in @a data
 * @return #GNUNET_OK on success
 */
static int
gns_string_to_value (void *cls,
                     uint32_t type,
                     const char *s,
                     void **data,
                     size_t *data_size)
{
  struct GNUNET_CRYPTO_EcdsaPublicKey pkey;

  if (NULL == s)
    return GNUNET_SYSERR;
  switch (type)
  {

  case GNUNET_GNSRECORD_TYPE_PKEY:
    if (GNUNET_OK !=
	GNUNET_CRYPTO_ecdsa_public_key_from_string (s, strlen (s), &pkey))
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
           _("Unable to parse PKEY record `%s'\n"),
           s);
      return GNUNET_SYSERR;
    }
    *data = GNUNET_new (struct GNUNET_CRYPTO_EcdsaPublicKey);
    memcpy (*data, &pkey, sizeof (pkey));
    *data_size = sizeof (struct GNUNET_CRYPTO_EcdsaPublicKey);
    return GNUNET_OK;

  case GNUNET_GNSRECORD_TYPE_NICK:
    *data = GNUNET_strdup (s);
    *data_size = strlen (s);
    return GNUNET_OK;
  case GNUNET_GNSRECORD_TYPE_LEHO:
    *data = GNUNET_strdup (s);
    *data_size = strlen (s);
    return GNUNET_OK;
  case GNUNET_GNSRECORD_TYPE_GNS2DNS:
    {
      char nsbuf[514];
      char *cpy;
      char *at;
      size_t off;

      cpy = GNUNET_strdup (s);
      at = strchr (cpy, '@');
      if (NULL == at)
      {
        GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                    _("Unable to parse GNS2DNS record `%s'\n"),
                    s);
        GNUNET_free (cpy);
        return GNUNET_SYSERR;
      }
      *at = '\0';
      at++;

      off = 0;
      if ( (GNUNET_OK !=
            GNUNET_DNSPARSER_builder_add_name (nsbuf,
                                               sizeof (nsbuf),
                                               &off,
                                               cpy)) ||
           (GNUNET_OK !=
            GNUNET_DNSPARSER_builder_add_name (nsbuf,
                                               sizeof (nsbuf),
                                               &off,
                                               at)) )
      {
	GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                    _("Failed to serialize GNS2DNS record with value `%s'\n"),
                    s);
        GNUNET_free (cpy);
	return GNUNET_SYSERR;
      }
      GNUNET_free (cpy);
      *data_size = off;
      *data = GNUNET_malloc (off);
      memcpy (*data, nsbuf, off);
      return GNUNET_OK;
    }
  case GNUNET_GNSRECORD_TYPE_VPN:
    {
      struct GNUNET_TUN_GnsVpnRecord *vpn;
      char s_peer[103 + 1];
      char s_serv[253 + 1];
      unsigned int proto;

      if (3 != SSCANF (s,
                       "%u %103s %253s",
                       &proto, s_peer, s_serv))
      {
        GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                    _("Unable to parse VPN record string `%s'\n"),
                    s);
        return GNUNET_SYSERR;
      }
      *data_size = sizeof (struct GNUNET_TUN_GnsVpnRecord) + strlen (s_serv) + 1;
      *data = vpn = GNUNET_malloc (*data_size);
      if (GNUNET_OK != GNUNET_CRYPTO_eddsa_public_key_from_string ((char*) s_peer,
                                                                   strlen (s_peer),
                                                                   &vpn->peer.public_key))
      {
        GNUNET_free (vpn);
        *data_size = 0;
        return GNUNET_SYSERR;
      }
      vpn->proto = htons ((uint16_t) proto);
      strcpy ((char*)&vpn[1], s_serv);
      return GNUNET_OK;
    }
  case GNUNET_GNSRECORD_TYPE_BOX:
    {
      struct GNUNET_GNSRECORD_BoxRecord *box;
      size_t rest;
      unsigned int protocol;
      unsigned int service;
      unsigned int record_type;
      void *bval;
      size_t bval_size;

      if (3 != SSCANF (s,
                       "%u %u %u ",
                       &protocol,
                       &service,
                       &record_type))
      {
        GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                    _("Unable to parse BOX record string `%s'\n"),
                    s);
        return GNUNET_SYSERR;
      }
      rest = snprintf (NULL, 0,
                       "%u %u %u ",
                       protocol,
                       service,
                       record_type);
      if (GNUNET_OK !=
          GNUNET_GNSRECORD_string_to_value (record_type,
                                            &s[rest],
                                            &bval,
                                            &bval_size))
        return GNUNET_SYSERR;
      *data_size = sizeof (struct GNUNET_GNSRECORD_BoxRecord) + bval_size;
      *data = box = GNUNET_malloc (*data_size);
      box->protocol = htons (protocol);
      box->service = htons (service);
      box->record_type = htonl (record_type);
      memcpy (&box[1],
              bval,
              bval_size);
      GNUNET_free (bval);
      return GNUNET_OK;
    }
  default:
    return GNUNET_SYSERR;
  }
}