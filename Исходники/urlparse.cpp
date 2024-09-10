void UrlParse::setString(const char *urlstring) {
  protocol = hostname = path = resource = NULL;
  port = 0;
  // parse etc
  String cp(urlstring);
  char *colon = STRCHR(cp, ':');
  if (colon == NULL || colon > cp.v()+4) {	// new default_protocol method
    setProtocol(default_protocol);
  } else {
    String p = cp, tmp(colon+1);
    p.changeChar(':', '\0');
    setProtocol(p);
    cp = tmp;
  }
  // eat slashes
  while (cp.v()[0] == '/') {
    String tmp = cp.v()+1;
    cp = tmp;
  }
  char *firstslash = STRCHR(cp, '/');
  if (firstslash == NULL) {	// host only
    hostname = cp;
    return;
  } else {
    String tmp = firstslash+1;
    *firstslash = '\0';
    hostname = cp;
    cp = tmp;
  }

  colon = STRCHR(hostname, ':');	// reusing
  if (colon != NULL) {
    *colon = '\0';
    port = ATOI(colon+1);
    if (port == 0) port = 80;
  }

  if (!cp.isempty()) {
    char *lastslash;
    for (lastslash = (char*)cp.v(); *lastslash; lastslash++) { }	// go to end
    // back up to last slash or beginning
    for (; lastslash > (char*)cp.v() && *lastslash != '/'; lastslash--) { }

    if (*lastslash == '/') {
      resource = lastslash+1;
      *lastslash = '\0';
      path = cp;
    } else {
      resource = cp;	// no more slashes, just the filename->no path
      // path is already NULL
    }
  }
//  resolveDotDot();
}