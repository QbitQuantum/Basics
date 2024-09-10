/**
 * Handler for RENAME message from client, creates
 * new identity.
 *
 * @param cls unused
 * @param client who sent the message
 * @param message the message received
 */
static void
handle_rename_message (void *cls, struct GNUNET_SERVER_Client *client,
		       const struct GNUNET_MessageHeader *message)
{
  const struct GNUNET_IDENTITY_RenameMessage *rm;
  uint16_t size;
  uint16_t old_name_len;
  uint16_t new_name_len;
  struct Ego *ego;
  const char *old_name;
  const char *new_name;
  struct RenameContext rename_ctx;
  char *fn_old;
  char *fn_new;

  GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
	      "Received RENAME message from client\n");
  size = ntohs (message->size);
  if (size <= sizeof (struct GNUNET_IDENTITY_RenameMessage))
  {
    GNUNET_break (0);
    GNUNET_SERVER_receive_done (client, GNUNET_SYSERR);
    return;
  }
  rm = (const struct GNUNET_IDENTITY_RenameMessage *) message;
  old_name_len = ntohs (rm->old_name_len);
  new_name_len = ntohs (rm->new_name_len);
  old_name = (const char *) &rm[1];
  new_name = &old_name[old_name_len];
  if ( (old_name_len + new_name_len + sizeof (struct GNUNET_IDENTITY_RenameMessage) != size) ||
       ('\0' != old_name[old_name_len - 1]) ||
       ('\0' != new_name[new_name_len - 1]) )
  {
    GNUNET_break (0);
    GNUNET_SERVER_receive_done (client, GNUNET_SYSERR);
    return;
  }

  /* check if new name is already in use */
  for (ego = ego_head; NULL != ego; ego = ego->next)
  {
    if (0 == strcmp (ego->identifier,
		     new_name))
    {
      send_result_code (client, 1, gettext_noop ("target name already exists"));
      GNUNET_SERVER_receive_done (client, GNUNET_OK);
      return;
    }
  }

  /* locate old name and, if found, perform rename */
  for (ego = ego_head; NULL != ego; ego = ego->next)
  {
    if (0 == strcmp (ego->identifier,
		     old_name))
    {
      fn_old = get_ego_filename (ego);
      GNUNET_free (ego->identifier);
      rename_ctx.old_name = old_name;
      rename_ctx.new_name = new_name;
      GNUNET_CONFIGURATION_iterate_sections (subsystem_cfg,
					     &handle_ego_rename,
					     &rename_ctx);
      if (GNUNET_OK !=
	  GNUNET_CONFIGURATION_write (subsystem_cfg,
				      subsystem_cfg_file))
	GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
		    _("Failed to write subsystem default identifier map to `%s'.\n"),
		    subsystem_cfg_file);
      ego->identifier = GNUNET_strdup (new_name);
      fn_new = get_ego_filename (ego);
      if (0 != RENAME (fn_old, fn_new))
	GNUNET_log_strerror_file (GNUNET_ERROR_TYPE_WARNING, "rename", fn_old);
      GNUNET_free (fn_old);
      GNUNET_free (fn_new);
      notify_listeners (ego);
      send_result_code (client, 0, NULL);
      GNUNET_SERVER_receive_done (client, GNUNET_OK);
      return;
    }
  }

  /* failed to locate old name */
  send_result_code (client, 1, gettext_noop ("no matching ego found"));
  GNUNET_SERVER_receive_done (client, GNUNET_OK);
}