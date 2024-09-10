int
mdns_register(char *name, char *regtype, int port, char **txt)
{
  struct mdns_service *s;
  DNSServiceErrorType err;
  int i;
  char *eq;

  DPRINTF(E_DBG, L_MDNS, "Adding mDNS service '%s.%s'\n", name, regtype);

  s = calloc(1, sizeof(*s));
  if (!s)
    {
      DPRINTF(E_LOG, L_MDNS, "Out of memory registering service.\n");
      return -1;
    }
  TXTRecordCreate(&(s->txtRecord), 0, NULL);

  for (i = 0; txt && txt[i]; i++)
    {
      if ((eq = strchr(txt[i], '=')))
        {
          *eq = '\0';
          eq++;
          err = TXTRecordSetValue(&(s->txtRecord), txt[i], strlen(eq) * sizeof(char), eq);
          *(--eq) = '=';
          if (err != kDNSServiceErr_NoError)
            {
              DPRINTF(E_LOG, L_MDNS, "Could not set TXT record value\n");
              return mdns_service_free(s);
            }
        }
    }

  s->sdref = mdns_sdref_main;
  err = DNSServiceRegister(&(s->sdref), kDNSServiceFlagsShareConnection, 0,
                           name, regtype, NULL, NULL, htons(port),
                           TXTRecordGetLength(&(s->txtRecord)),
                           TXTRecordGetBytesPtr(&(s->txtRecord)),
                           mdns_register_callback, NULL);

  if (err != kDNSServiceErr_NoError)
    {
      DPRINTF(E_LOG, L_MDNS, "Error registering service '%s.%s'\n",
              name, regtype);
      s->sdref = NULL;
      return mdns_service_free(s);
    }

  s->next = mdns_services;
  mdns_services = s;

  return 0;
}