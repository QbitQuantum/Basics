static int mdns_dns_sd_register(char *apname, int port) {
  char *recordwithoutmetadata[] = {MDNS_RECORD_WITHOUT_METADATA, NULL};
#ifdef CONFIG_METADATA
  char *recordwithmetadata[] = {MDNS_RECORD_WITH_METADATA, NULL};
#endif
  char **record;
#ifdef CONFIG_METADATA
  if (config.metadata_enabled)
    record = recordwithmetadata;
  else
#endif
    record = recordwithoutmetadata;

  uint16_t length = 0;
  char **field;

  // Concatenate string contained i record into buf.

  for (field = record; *field; field++) {
    length += strlen(*field) + 1; // One byte for length each time
  }

  char *buf = malloc(length * sizeof(char));
  if (buf == NULL) {
    warn("dns_sd: buffer record allocation failed");
    return -1;
  }

  char *p = buf;

  for (field = record; *field; field++) {
    char *newp = stpcpy(p + 1, *field);
    *p = newp - p - 1;
    p = newp;
  }

  DNSServiceErrorType error;
  error = DNSServiceRegister(&service, 0, kDNSServiceInterfaceIndexAny, apname, config.regtype, "",
                             NULL, htons((uint16_t)port), length, buf, NULL, NULL);

  free(buf);

  if (error == kDNSServiceErr_NoError)
    return 0;
  else {
    warn("dns-sd: DNSServiceRegister error %d", error);
    return -1;
  }
}