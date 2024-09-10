pgp_key_t pgp_ask_for_key (char *tag, char *whatfor,
                           short abilities, pgp_ring_t keyring)
{
  pgp_key_t key;
  char resp[SHORT_STRING];
  struct pgp_cache *l = NULL;

  mutt_clear_error ();

  resp[0] = 0;
  if (whatfor)
  {

    for (l = id_defaults; l; l = l->next)
      if (!mutt_strcasecmp (whatfor, l->what))
      {
	strfcpy (resp, NONULL (l->dflt), sizeof (resp));
	break;
      }
  }


  FOREVER
  {
    resp[0] = 0;
    if (mutt_get_field (tag, resp, sizeof (resp), M_CLEAR) != 0)
      return NULL;

    if (whatfor)
    {
      if (l)
	mutt_str_replace (&l->dflt, resp);
      else
      {
	l = safe_malloc (sizeof (struct pgp_cache));
	l->next = id_defaults;
	id_defaults = l;
	l->what = safe_strdup (whatfor);
	l->dflt = safe_strdup (resp);
      }
    }

    if ((key = pgp_getkeybystr (resp, abilities, keyring)))
      return key;

    BEEP ();
  }
  /* not reached */
}