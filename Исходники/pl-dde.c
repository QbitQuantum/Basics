word
pl_open_dde_conversation(term_t service, term_t topic, term_t handle)
{ UINT i;
  HSZ Hservice, Htopic;

  if ( !dde_initialise() )
    fail;

  if ( !get_hsz(service, &Hservice) ||
       !get_hsz(topic, &Htopic) )
    fail;

  /* Establish a connection and get a handle for it */
  for (i=0; i < MAX_CONVERSATIONS; i++)   /* Find an open slot */
  { if (conv_handle[i] == (HCONV)NULL)
      break;
  }
  if (i == MAX_CONVERSATIONS)
    return PL_error(NULL, 0, NULL, ERR_RESOURCE, ATOM_max_dde_handles);

  if ( !(conv_handle[i] = DdeConnect(ddeInst, Hservice, Htopic, 0)) )
    fail;

  DdeFreeStringHandle(ddeInst, Hservice);
  DdeFreeStringHandle(ddeInst, Htopic);

  return PL_unify_integer(handle, i);
}