// A special version of "parseTransportHeader()", used just for parsing the "Transport:" header in an incoming "REGISTER" command:
void parseTransportHeaderForREGISTER(char const* buf,
				     Boolean &reuseConnection,
				     Boolean& deliverViaTCP,
				     char*& proxyURLSuffix) {
  // Initialize the result parameters to default values:
  reuseConnection = False;
  deliverViaTCP = False;
  proxyURLSuffix = NULL;
  
  // First, find "Transport:"
  while (1) {
    if (*buf == '\0') return; // not found
    if (*buf == '\r' && *(buf+1) == '\n' && *(buf+2) == '\r') return; // end of the headers => not found
    if (_strncasecmp(buf, "Transport:", 10) == 0) break;
    ++buf;
  }
  
  // Then, run through each of the fields, looking for ones we handle:
  char const* fields = buf + 10;
  while (*fields == ' ') ++fields;
  char* field = strDupSize(fields);
  while (sscanf(fields, "%[^;\r\n]", field) == 1) {
    if (strcmp(field, "reuse_connection") == 0) {
      reuseConnection = True;
    } else if (_strncasecmp(field, "preferred_delivery_protocol=udp", 31) == 0) {
      deliverViaTCP = False;
    } else if (_strncasecmp(field, "preferred_delivery_protocol=interleaved", 39) == 0) {
      deliverViaTCP = True;
    } else if (_strncasecmp(field, "proxy_url_suffix=", 17) == 0) {
      delete[] proxyURLSuffix;
      proxyURLSuffix = strDup(field+17);
    }
    
    fields += strlen(field);
    while (*fields == ';' || *fields == ' ' || *fields == '\t') ++fields; // skip over separating ';' chars or whitespace
    if (*fields == '\0' || *fields == '\r' || *fields == '\n') break;
  }
  delete[] field;
}