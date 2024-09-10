void dictstat_read (hashcat_ctx_t *hashcat_ctx)
{
  hashconfig_t   *hashconfig   = hashcat_ctx->hashconfig;
  dictstat_ctx_t *dictstat_ctx = hashcat_ctx->dictstat_ctx;

  if (dictstat_ctx->enabled == false) return;

  if (hashconfig->dictstat_disable == true) return;

  FILE *fp = fopen (dictstat_ctx->filename, "rb");

  if (fp == NULL)
  {
    // first run, file does not exist, do not error out

    return;
  }

  // parse header

  u64 v;
  u64 z;

  const size_t nread1 = hc_fread (&v, sizeof (u64), 1, fp);
  const size_t nread2 = hc_fread (&z, sizeof (u64), 1, fp);

  if ((nread1 != 1) || (nread2 != 1))
  {
    event_log_error (hashcat_ctx, "%s: Invalid header", dictstat_ctx->filename);

    fclose (fp);

    return;
  }

  v = byte_swap_64 (v);
  z = byte_swap_64 (z);

  if ((v & 0xffffffffffffff00) != (DICTSTAT_VERSION & 0xffffffffffffff00))
  {
    event_log_error (hashcat_ctx, "%s: Invalid header, ignoring content", dictstat_ctx->filename);

    fclose (fp);

    return;
  }

  if (z != 0)
  {
    event_log_error (hashcat_ctx, "%s: Invalid header, ignoring content", dictstat_ctx->filename);

    fclose (fp);

    return;
  }

  if ((v & 0xff) < (DICTSTAT_VERSION & 0xff))
  {
    event_log_warning (hashcat_ctx, "%s: Outdated header version, ignoring content", dictstat_ctx->filename);

    fclose (fp);

    return;
  }

  // parse data

  while (!feof (fp))
  {
    dictstat_t d;

    const size_t nread = hc_fread (&d, sizeof (dictstat_t), 1, fp);

    if (nread == 0) continue;

    lsearch (&d, dictstat_ctx->base, &dictstat_ctx->cnt, sizeof (dictstat_t), sort_by_dictstat);

    if (dictstat_ctx->cnt == MAX_DICTSTAT)
    {
      event_log_error (hashcat_ctx, "There are too many entries in the %s database. You have to remove/rename it.", dictstat_ctx->filename);

      break;
    }
  }

  fclose (fp);
}