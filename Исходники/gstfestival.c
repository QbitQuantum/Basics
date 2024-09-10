static GstFlowReturn
gst_festival_chain (GstPad * pad, GstBuffer * buf)
{
  GstFlowReturn ret = GST_FLOW_OK;
  GstFestival *festival;
  guint8 *p, *ep;
  gint f;
  FILE *fd;

  festival = GST_FESTIVAL (GST_PAD_PARENT (pad));

  GST_LOG_OBJECT (festival, "Got text buffer, %u bytes", GST_BUFFER_SIZE (buf));

  f = dup (festival->info->server_fd);
  if (f < 0)
    goto fail_open;
  fd = fdopen (f, "wb");
  if (fd == NULL) {
    close (f);
    goto fail_open;
  }

  /* Copy text over to server, escaping any quotes */
  fprintf (fd, "(Parameter.set 'Audio_Required_Rate 16000)\n");
  fflush (fd);
  GST_DEBUG_OBJECT (festival, "issued Parameter.set command");
  if (read_response (festival) == FALSE) {
    fclose (fd);
    goto fail_read;
  }

  fprintf (fd, "(tts_textall \"");
  p = GST_BUFFER_DATA (buf);
  ep = p + GST_BUFFER_SIZE (buf);
  for (; p < ep && (*p != '\0'); p++) {
    if ((*p == '"') || (*p == '\\')) {
      putc ('\\', fd);
    }

    putc (*p, fd);
  }
  fprintf (fd, "\" \"%s\")\n", festival->info->text_mode);
  fclose (fd);

  GST_DEBUG_OBJECT (festival, "issued tts_textall command");

  /* Read back info from server */
  if (read_response (festival) == FALSE)
    goto fail_read;

out:
  gst_buffer_unref (buf);
  return ret;

  /* ERRORS */
fail_open:
  {
    GST_ELEMENT_ERROR (festival, RESOURCE, OPEN_WRITE, (NULL), (NULL));
    ret = GST_FLOW_ERROR;
    goto out;
  }
fail_read:
  {
    GST_ELEMENT_ERROR (festival, RESOURCE, READ, (NULL), (NULL));
    ret = GST_FLOW_ERROR;
    goto out;
  }
}