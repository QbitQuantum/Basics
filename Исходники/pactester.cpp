int
main(int argc, char* argv[])
{
  const char *pacfile = NULL, *host = NULL, *url = NULL, *urlsfile = NULL,
             *client_ip = NULL, *dns_servers = NULL, *dns_domains = NULL;
  int dns_resolver_variant = DNS_GETADDRINFO;

  int enable_microsoft_extensions = 1;

  if (argv[1] && (STREQ(argv[1], "--help") || STREQ(argv[1], "--helpshort"))) {
    usage(argv[0]);
  }

  signed char c;
  while ((c = getopt(argc, argv, "eEvp:u:h:f:c:s:d:r:")) != -1)
    switch (c)
    {
      case 'v':
        printf("%s\n", pacparser_version());
        return 0;
      case 'p':
        pacfile = optarg;
        break;
      case 'u':
        url = optarg;
        break;
      case 'h':
        host = optarg;
        break;
      case 'f':
        urlsfile = optarg;
        break;
      case 'c':
        client_ip = optarg;
        break;
      case 's':
        dns_servers = optarg;
        break;
      case 'd':
        dns_domains = optarg;
        break;
      case 'r':
        if (!strcmp(optarg, "none"))
        {
            dns_resolver_variant = DNS_NONE;
        }
        else if (!strcmp(optarg, "getaddrinfo"))
        {
            dns_resolver_variant = DNS_GETADDRINFO;
        }
        else if (!strcmp(optarg, "c-ares"))
        {
            dns_resolver_variant = DNS_C_ARES;
        }
        else
        {
            usage(argv[0]);
            abort();
        }
        break;
     case 'e':
        enable_microsoft_extensions = 1;
        break;
     case 'E':
        enable_microsoft_extensions = 0;
        break;
      case '?':
        usage(argv[0]);
        /* fallthrough */
      default:
        abort();
    }

  if (!pacfile) {
    fprintf(stderr, __FILE__": You didn't specify the PAC file\n");
    usage(argv[0]);
  }
  if (!url && !urlsfile) {
    fprintf(stderr, __FILE__": You didn't specify a URL or URL-FILE\n");
    usage(argv[0]);
  }
  if (url && urlsfile) {
    fprintf(stderr, __FILE__": You can't specify both URL and URL-FILE\n");
    usage(argv[0]);
  }

  std::unique_ptr<PacParser> parser = PacParser::create(
    dns_servers, dns_domains, enable_microsoft_extensions);

  if (!parser->set_dns_resolver_variant(dns_resolver_variant))
    usage(argv[0]);

  // Read pacfile from stdin.
  if (STREQ("-", pacfile)) {
    char *script;
    size_t script_size = 1;  // for the null terminator
    char buffer[LINEMAX];

    script = (char*)calloc(1, sizeof(char));
    if (script == NULL) {
      perror(__FILE__": Failed to allocate the memory for the script");
      return 1;
    }

    while (fgets(buffer, sizeof(buffer), stdin)) {
      if (strlen(buffer) == 0)
        break;
      char *old = script;
      script_size += strlen(buffer);
      if (script_size > PACMAX) {
        fprintf(stderr, __FILE__": Input file is too big. "
                "Maximum allowed size in bytes is: %d\n", PACMAX);
        free(script);
        return 1;
      }
      script = (char*)realloc(script, script_size);
      if (script == NULL) {
        perror(__FILE__": Failed to allocate the memory for the script");
        free(old);
        return 1;
      }
      strncat(script, buffer, strlen(buffer));
    }

    if (ferror(stdin)) {
      free(script);
      perror(__FILE__": Error reading from stdin");
      return 1;
    }

    if (!parser->parse_pac_string(script)) {
      fprintf(stderr, __FILE__": Could not parse the pac script '%s'\n",
              script);
      free(script);
      return 1;
    }
    free(script);
  }
  else {
    if (!parser->parse_pac_file(pacfile)) {
      fprintf(stderr, __FILE__": Could not parse the pac file: %s\n",
              pacfile);
      return 1;
    }
  }

  if (client_ip)
    parser->setmyip(client_ip);

  char *h;
  std::string proxy;
  int rc = 0;

  if (url) {
    if (host) {
      parser->find_proxy(url, host, proxy);
    } else {
      // If the host was not explicitly given, get it from the URL.
      // If that fails, return with error (the get_host_from_url()
      // function will print a proper error message in that case).
      if ((h = get_host_from_url(url)) == NULL) {
        return 1;
      }
      parser->find_proxy(url, h, proxy);
      free(h);
    }
    if (!proxy.length()) {
      fprintf(stderr, __FILE__": Problem in finding proxy for %s\n", url);
      return 1;
    }
    printf("%s\n", proxy.c_str());
  }

  else if (urlsfile) {
    char line[LINEMAX];
    FILE *fp;
    if ((fp = fopen(urlsfile, "r")) == NULL) {
      fprintf(stderr, __FILE__": Could not open urlsfile '%s'\n", urlsfile);
      return 1;
    }
    while (fgets(line, sizeof(line), fp)) {
      char *url = line;
      // Remove spaces from the beginning.
      while (*url == ' ' || *url == '\t')
        url++;
      // Skip comment lines.
      if (*url == '#') {
        printf("%s", url);
        continue;
      }
      char *urlend = url;
      while (*urlend != '\r' && *urlend != '\n' && *urlend != '\0' &&
             *urlend != ' ' && *urlend != '\t')
        urlend++;  // keep moving till you hit space or end of string
      *urlend = '\0';
      if ((h = get_host_from_url(url)) == NULL) {
        rc = 1;  // will exit with error
        continue;
      }
      parser->find_proxy(url, h, proxy);
      free(h);
      if (!proxy.length()) {
        fprintf(stderr, __FILE__": Problem in finding proxy for %s\n", url);
        rc = 1; // will exit with error
        continue;
      }
      printf("%s : %s\n", url, proxy.c_str());
    }
    fclose(fp);
  }

  return rc;
}