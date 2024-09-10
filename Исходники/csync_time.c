/* check time difference between the replicas */
time_t csync_timediff(CSYNC *ctx) {
  time_t timediff = -1;
  char errbuf[256] = {0};
  char *luri = NULL;
  char *ruri = NULL;
  csync_vio_handle_t *fp = NULL;
  csync_vio_file_stat_t *st = NULL;
  csync_vio_handle_t *dp = NULL;

  /* try to open remote dir to get auth */
  ctx->replica = ctx->remote.type;
  dp = csync_vio_opendir(ctx, ctx->remote.uri);
  if (dp == NULL) {
    /*
     * To prevent problems especially with pam_csync we shouldn't try to create the
     * remote directory here. Just fail!
     */
    strerror_r(errno, errbuf, sizeof(errbuf));
    CSYNC_LOG(CSYNC_LOG_PRIORITY_FATAL,
        "Access dienied to remote uri: %s - %s",
        ctx->remote.uri,
        errbuf);
    return -1;
  }
  csync_vio_closedir(ctx, dp);

  if (asprintf(&luri, "%s/.csync_timediff.ctmp", ctx->local.uri) < 0) {
    goto out;
  }

  if (asprintf(&ruri, "%s/.csync_timediff.ctmp", ctx->remote.uri) < 0) {
    goto out;
  }

  /* create temporary file on local */
  ctx->replica = ctx->local.type;
  fp = csync_vio_creat(ctx, luri, 0644);
  if (fp == NULL) {
    strerror_r(errno, errbuf, sizeof(errbuf));
    CSYNC_LOG(CSYNC_LOG_PRIORITY_FATAL,
        "Unable to create temporary file: %s - %s",
        luri,
        errbuf);
    goto out;
  }
  csync_vio_close(ctx, fp);

  /* Get the modification time */
  st = csync_vio_file_stat_new();
  if (csync_vio_stat(ctx, luri, st) < 0) {
    strerror_r(errno, errbuf, sizeof(errbuf));
    CSYNC_LOG(CSYNC_LOG_PRIORITY_FATAL,
        "Synchronisation is not possible! %s - %s",
        luri,
        errbuf);
    goto out;
  }
  timediff = st->mtime;
  csync_vio_file_stat_destroy(st);
  st = NULL;

  /* create temporary file on remote replica */
  ctx->replica = ctx->remote.type;

  fp = csync_vio_creat(ctx, ruri, 0644);
  if (fp == NULL) {
    strerror_r(errno, errbuf, sizeof(errbuf));
    CSYNC_LOG(CSYNC_LOG_PRIORITY_FATAL,
        "Unable to create temporary file: %s - %s",
        ruri,
        errbuf);
    goto out;
  }
  csync_vio_close(ctx, fp);

  /* Get the modification time */
  st = csync_vio_file_stat_new();
  if (csync_vio_stat(ctx, ruri, st) < 0) {
    strerror_r(errno, errbuf, sizeof(errbuf));
    CSYNC_LOG(CSYNC_LOG_PRIORITY_FATAL,
        "Synchronisation is not possible! %s - %s",
        ruri,
        errbuf);
    goto out;
  }

  /* calc time difference */
  timediff = llabs(timediff - st->mtime);
  CSYNC_LOG(CSYNC_LOG_PRIORITY_DEBUG, "Time difference: %ld seconds", timediff);

out:
  csync_vio_file_stat_destroy(st);

  ctx->replica = ctx->local.type;
  csync_vio_unlink(ctx, luri);
  SAFE_FREE(luri);

  ctx->replica = ctx->remote.type;
  csync_vio_unlink(ctx, ruri);
  SAFE_FREE(ruri);

  return timediff;
}