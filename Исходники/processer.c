int analyze_line(char *line[]) {
  char sec[LINE_COLUMNS];
  struct tm *tm;
  struct sockaddr_in sa;
  char *l[LINE_COLUMNS];
  char date[9];
  char host[30];
  //char cn_host[CN_LENGTH];
  long i_tmp = 0;
  char *c_tmp;
  struct in_addr addr;

  memset(sec, 0, sizeof(sec));
  memset(date, 0, sizeof(date));
  sscanf(line[0], "%[^-]", sec);
  i_tmp = atol(sec);
  tm = localtime(&i_tmp);
  if(tm == NULL) {
    fprintf(stderr, "  Error to parse time %s\n", sec);
    return EXIT_FAILURE;
  }

  if(strftime(date, sizeof(date), "%Y%m%d", tm) == 0) {
    fprintf(stderr, "  Error to change time to human readable strings\n");
    return EXIT_FAILURE;
  }
  l[0] = date;
  
  if(ip4insubnet(line[2], LOCAL_NET, LOCAL_NETBITS) == 1) {
    c_tmp = line[2];
    l[2] = line[3];
    if(line[6] != NULL && strcasecmp(line[4], "TCP") == 0) {
      l[5] = line[6];
    }
  }
  else{
    c_tmp = line[3];
    l[2] = line[2];
    if(line[5] != NULL && strcasecmp(line[4], "TCP") == 0) {
      l[5] = line[5];
    }
  } 
  
  memset(host, 0, sizeof(host));
  bzero(&sa, sizeof(struct sockaddr_in));
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = inet_addr(c_tmp);
  getnameinfo((struct sockaddr *)&sa, sizeof(sa), host, sizeof(host), NULL, 0, NI_NOFQDN);
  if(strlen(host) <= 0) l[1] = c_tmp;
  else l[1] = host;

  l[3] = line[4];
  l[4] = line[1];

  l[7] = "\0";
  if(strcasecmp(line[4], "TCP") == 0) {
    if(strcasecmp(line[7], "FA") == 0) l[6] = "1";
    else l[6] = "0";

    for(i_tmp = 8; i_tmp < LINE_COLUMNS; i_tmp++) {
      if(strcmp(line[i_tmp], "\n") == 0) {
        l[i_tmp] = NULL;
        break;  
      }
      l[i_tmp] = line[i_tmp]; 
    }

    /*
    if(i_tmp == 8 && (atoi(l[5]) == 443 || atoi(l[5]) == 8443)) {
      cn_host[0] = '\0';
      pthread_mutex_lock(&mutex);
      get_crt_cn(l[2], l[5], cn_host); 
      pthread_mutex_unlock(&mutex);
      l[7] = cn_host;
    }
    */

  } else {
    l[5] = NULL;
    l[6] = NULL;
  }

  db_save(l);
}