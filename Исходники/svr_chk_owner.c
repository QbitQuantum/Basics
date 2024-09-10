int authenticate_user(

  struct batch_request *preq,  /* I */
  struct credential    *pcred,
  char   **autherr) /* O */

  {
  int    rc;
  char   uath[PBS_MAXUSER + PBS_MAXHOSTNAME + 1];
  time_t time_now = time(NULL);
  char   error_msg[1024];
  long   acl_enabled = FALSE;

#ifdef MUNGE_AUTH
 
  if (strncmp(preq->rq_user, pcred->username, PBS_MAXUSER))
    {
    /* extra check for munge */
    struct array_strings *my_acl = NULL;
    char uh[PBS_MAXUSER + PBS_MAXHOSTNAME + 2];

    sprintf(uh, "%s@%s", preq->rq_user, pcred->hostname);
    
    get_svr_attr_arst(SRV_ATR_authusers, &my_acl); 
    if ((acl_check_my_array_string(my_acl, uh, ACL_User_Host)) == 0)
      {
      *autherr = strdup("User not in authorized user list.");
      sprintf(error_msg, "%s Requested user %s: requested from host %s",
                     *autherr, preq->rq_user, preq->rq_host);
      log_event(PBSEVENT_ADMIN, PBS_EVENTCLASS_SERVER, __func__, error_msg);
      return(PBSE_BADCRED);
      }
    }
#else
  if (strncmp(preq->rq_user, pcred->username, PBS_MAXUSER))
    {
    *autherr = strdup("Users do not match");
    sprintf(error_msg, "%s: Requested user %s: credential user %s: requested from host %s",
                   *autherr, preq->rq_user, pcred->username, preq->rq_host);
    log_event(PBSEVENT_ADMIN, PBS_EVENTCLASS_SERVER, __func__, error_msg);
    return(PBSE_BADCRED);
    }
#endif

  if (strncmp(preq->rq_host, pcred->hostname, PBS_MAXHOSTNAME))
    {
    struct sockaddr_in *sai1;
    struct sockaddr_in *sai2;
    struct addrinfo    *addr_info1 = NULL;
    struct addrinfo    *addr_info2 = NULL;

    sai1 = get_cached_addrinfo(preq->rq_host);
    sai2 = get_cached_addrinfo(pcred->hostname);

    if ((sai1 == NULL) &&
        (getaddrinfo(preq->rq_host, NULL, NULL, &addr_info1) == PBSE_NONE))
      {
      sai1 = (struct sockaddr_in *)addr_info1->ai_addr;
      insert_addr_name_info(preq->rq_host, addr_info1->ai_canonname, sai1);
      }

    if ((sai2 == NULL) &&
        (getaddrinfo(pcred->hostname, NULL, NULL, &addr_info2) == PBSE_NONE))
      {
      sai2 = (struct sockaddr_in *)addr_info2->ai_addr;
      insert_addr_name_info(pcred->hostname, addr_info2->ai_canonname, sai2);
      }

    if ((sai1 == NULL) ||
        (sai2 == NULL) ||
        (memcmp(sai1, sai2, sizeof(struct sockaddr_in))))
      {
      *autherr = strdup("Hosts do not match");
      
      sprintf(error_msg, "%s: Requested host %s: credential host: %s",
        *autherr, preq->rq_host, pcred->hostname);
      log_event(PBSEVENT_ADMIN, PBS_EVENTCLASS_SERVER, __func__, error_msg);
    
      if (addr_info1 != NULL)
        freeaddrinfo(addr_info1);
      if (addr_info2 != NULL)
        freeaddrinfo(addr_info2);
      
      return(PBSE_BADCRED);
      }
      
    if (addr_info1 != NULL)
      freeaddrinfo(addr_info1);
    if (addr_info2 != NULL)
      freeaddrinfo(addr_info2);
    }

  if (pcred->timestamp)
    {
    long lifetime = 0;
    if (get_svr_attr_l(SRV_ATR_CredentialLifetime, &lifetime) == PBSE_NONE)
      {
      /* use configured value if set */
      }
    else 
      {
      /* if not use the default */
      lifetime = CREDENTIAL_LIFETIME;
      }

    /* negative values mean that credentials have an infinite lifetime */
    if (lifetime > -1)
      {
      if ((pcred->timestamp - CREDENTIAL_TIME_DELTA > time_now) ||
          (pcred->timestamp + lifetime < time_now))
        {
        return(PBSE_EXPIRED);
        }
      }

    }

  /* If Server's Acl_User enabled, check if user in list */
  get_svr_attr_l(SRV_ATR_AclUserEnabled, &acl_enabled);
  if (acl_enabled)
    {
    struct array_strings *acl_users = NULL;
    snprintf(uath, sizeof(uath), "%s@%s", preq->rq_user, preq->rq_host);
    
    get_svr_attr_arst(SRV_ATR_AclUsers, &acl_users);
    if (acl_check_my_array_string(acl_users, uath, ACL_User) == 0)
      {

#ifdef __CYGWIN__
  if (!IamAdminByName(preq->rq_user) || (strcasecmp(preq->rq_host, server_host) != 0))
    {
	return(PBSE_PERM);
    }
#else /* __CYGWIN__ */
#ifdef PBS_ROOT_ALWAYS_ADMIN

      if ((strcmp(preq->rq_user, PBS_DEFAULT_ADMIN) != 0) ||
          (strcasecmp(preq->rq_host, server_host) != 0))
        {
        return(PBSE_PERM);
        }

#else /* PBS_ROOT_ALWAYS_ADMIN */
      return(PBSE_PERM);

#endif /* PBS_ROOT_ALWAYS_ADMIN */
#endif /* __CYGWIN__ */

      }
    }

  /* A site stub for additional checking */

  rc = site_allow_u(preq->rq_user, preq->rq_host);

  return(rc);
  }  /* END authenticate_user() */