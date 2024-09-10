static void
acmmp3dec_teardown (ACMMP3Dec * dec)
{
  if (dec->output_caps) {
    gst_caps_unref (dec->output_caps);
    dec->output_caps = NULL;
  }

  if (dec->header.fdwStatus & ACMSTREAMHEADER_STATUSF_PREPARED)
    acmStreamUnprepareHeader (dec->stream, &dec->header, 0);
  if (dec->header.pbSrc)
    g_free (dec->header.pbSrc);
  if (dec->header.pbDst)
    g_free (dec->header.pbDst);
  memset (&dec->header, 0, sizeof (dec->header));

  if (dec->stream) {
    acmStreamClose (dec->stream, 0);
    dec->stream = 0;
  }

  dec->timestamp = GST_CLOCK_TIME_NONE;
  dec->is_setup = FALSE;
}