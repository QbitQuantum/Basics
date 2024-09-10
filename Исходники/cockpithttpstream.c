static gboolean
relay_chunked (CockpitHttpStream *self,
               CockpitChannel *channel,
               GByteArray *buffer)
{
  GBytes *message;
  const gchar *data;
  const gchar *pos;
  guint64 size;
  gsize length;
  gsize beg;
  gchar *end;

  data = (const gchar *)buffer->data;
  length = buffer->len;

  pos = memchr (data, '\r', length);
  if (pos == NULL)
    return FALSE; /* want more data */

  beg = (pos + 2) - data;
  if (length < beg)
    {
      /* have to have a least the ending chars */
      return FALSE; /* want more data */
    }

  size = g_ascii_strtoull (data, &end, 16);
  if (pos[1] != '\n' || end != pos)
    {
      cockpit_channel_fail (channel, "protocol-error",
                            "%s: received invalid HTTP chunk", self->name);
    }
  else if (size > G_MAXSSIZE)
    {
      cockpit_channel_fail (channel, "protocol-error",
                            "%s: received extremely large HTTP chunk", self->name);
    }
  else if (length < beg + size + 2)
    {
      return FALSE; /* want more data */
    }
  else if (data[beg + size] != '\r' || data[beg + size + 1] != '\n')
    {
      cockpit_channel_fail (channel, "protocol-error",
                            "%s: received invalid HTTP chunk data", self->name);
    }
  else if (size == 0)
    {
      /* All done, yay */
      g_debug ("%s: received last chunk", self->name);
      cockpit_pipe_skip (buffer, beg + 2);
      cockpit_channel_close (channel, NULL);
      g_assert (self->state == FINISHED);
    }
  else
    {
      message = cockpit_pipe_consume (buffer, beg, size, 2);
      relay_data (channel, message);
      g_bytes_unref (message);
      return TRUE;
    }

  return TRUE;
}