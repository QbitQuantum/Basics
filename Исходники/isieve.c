/*
 * Initialize SASL and set necessary options
 */
int init_sasl(isieve_t *obj,
              int ssf,
              sasl_callback_t *callbacks)
{
  static int sasl_started = 0;
  int saslresult = SASL_OK;
  sasl_security_properties_t *secprops=NULL;
  socklen_t addrsize=sizeof(struct sockaddr_storage);
  struct sockaddr_storage saddr_l, saddr_r;
  char localip[60], remoteip[60];

  /* attempt to start sasl */
  if(!sasl_started) {
      saslresult=sasl_client_init(NULL);
      obj->conn = NULL;
      sasl_started = 1;
  }

  /* Save the callbacks array */
  obj->callbacks = callbacks;

  if (saslresult!=SASL_OK) return -1;

  addrsize=sizeof(struct sockaddr_storage);
  if (getpeername(obj->sock,(struct sockaddr *)&saddr_r,&addrsize)!=0)
      return -1;

  addrsize=sizeof(struct sockaddr_storage);
  if (getsockname(obj->sock,(struct sockaddr *)&saddr_l,&addrsize)!=0)
      return -1;
#if 0
  /* XXX  The following line causes problems with KERBEROS_V4 decoding.
   * We're not sure why its an issue, but this code isn't used in any of
   * our other client code (imtest.c, backend.c), so we're removing it.
   */
  /* set the port manually since getsockname is stupid and doesn't */
  ((struct sockaddr_in *)&saddr_l)->sin_port = htons(obj->port);
#endif
  if (iptostring((struct sockaddr *)&saddr_r, addrsize, remoteip, 60))
      return -1;

  if (iptostring((struct sockaddr *)&saddr_l, addrsize, localip, 60))
      return -1;

  if(obj->conn) sasl_dispose(&obj->conn);

  /* client new connection */
  saslresult=sasl_client_new(SIEVE_SERVICE_NAME,
                             obj->serverFQDN,
                             localip, remoteip,
                             callbacks,
                             SASL_SUCCESS_DATA,
                             &obj->conn);

  if (saslresult!=SASL_OK) return -1;

  /* create a security structure and give it to sasl */
  secprops = make_secprops(0, ssf);
  if (secprops != NULL)
  {
    sasl_setprop(obj->conn, SASL_SEC_PROPS, secprops);
    free(secprops);
  }

  return 0;
}