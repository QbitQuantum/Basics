static void
process_altavista_cookie(const char *cookie, char **new_cookie) {
  CookieNodeType *cl;
  ustring ucookie = USTRING_INITIALIZER;
  *new_cookie = NULL;

  cl = parse_cookies(cookie);
  if(!cl) {
    nag("Error parsing cookies\n");
    goto cleanup;
  }

  delete_cookie(&cl, "AV_ALL");
  if(set_cookie_value(&cl, " AV_PG", "1")) {
    nag("Error setting new cookie value\n");
    goto cleanup;
  }

  if(rebuild_cookie(cl, &ucookie)) {
    nag("Error rebuilding cookie\n");
    goto cleanup;
  }
  
  *new_cookie = Strdup(ucookie.string);

 cleanup:
  delete_cookie_list(cl);
  reset_ustring(&ucookie);
}