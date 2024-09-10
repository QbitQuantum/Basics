static void *search_thread(char *id) {
  LDAPMessage *res, *entry;
  char *dn, filter[40];
  int rc, opcount;
  void *voidrc = (void *)0;

  printf("Starting search_thread %s.\n", id);
  opcount = 0;
  tsd_setup();

  for (;;) {
    if (range_filters) {
      switch (get_random_id() % 3) {
        case 0:
          sprintf(filter, "(cn>=%d)", get_random_id());
          break;
        case 1:
          sprintf(filter, "(cn<=%d)", get_random_id());
          break;
        case 2:
          sprintf(filter, "(&(cn>=%d)(cn<=%d))", get_random_id(),
                  get_random_id());
          break;
      }
    } else {
      sprintf(filter, "cn=%d", get_random_id());
    }

    printf("Thread %s: Searching for entry (%s)\n", id, filter);

    res = NULL;
    if ((rc = ldap_search_ext_s(ld, BASE, SCOPE, filter, NULL, 0, NULL, NULL,
                                NULL, 0, &res)) != LDAP_SUCCESS) {
      ldap_perror(ld, "ldap_search_ext_s");
      if (rc == LDAP_SERVER_DOWN) {
        perror("ldap_search_ext_s");
        voidrc = (void *)1;
        goto search_cleanup_and_return;
      }
    }
    if (res != NULL) {
      entry = ldap_first_entry(ld, res);
      if (entry == NULL) {
        printf("Thread %s: found no entries\n", id);
      } else {
        dn = ldap_get_dn(ld, entry);
        printf("Thread %s: found entry (%s); %d total\n", id,
               dn == NULL ? "(Null)" : dn, ldap_count_entries(ld, res));
        ldap_memfree(dn);
      }
      ldap_msgfree(res);
    }

    ++opcount;
    if (maxops != 0 && opcount >= maxops) {
      break;
    }
  }

search_cleanup_and_return:
  printf("Thread %s: attempted %d search operations\n", id, opcount);
  set_ld_error(0, NULL, NULL, NULL); /* disposes of memory */
  tsd_cleanup();
  free(id);
  return voidrc;
}