/**
 * We've received an on-demand encoded block from the datastore.
 * Attempt to do on-demand encoding and (if successful), call the
 * continuation with the resulting block.  On error, clean up and ask
 * the datastore for more results.
 *
 * @param key key for the content
 * @param size number of bytes in data
 * @param data content stored
 * @param type type of the content
 * @param priority priority of the content
 * @param anonymity anonymity-level for the content
 * @param expiration expiration time for the content
 * @param uid unique identifier for the datum;
 *        maybe 0 if no unique identifier is available
 * @param cont function to call with the actual block (at most once, on success)
 * @param cont_cls closure for cont
 * @return GNUNET_OK on success
 */
int
GNUNET_FS_handle_on_demand_block (const struct GNUNET_HashCode * key, uint32_t size,
                                  const void *data, enum GNUNET_BLOCK_Type type,
                                  uint32_t priority, uint32_t anonymity,
                                  struct GNUNET_TIME_Absolute expiration,
                                  uint64_t uid,
                                  GNUNET_DATASTORE_DatumProcessor cont,
                                  void *cont_cls)
{
  const struct OnDemandBlock *odb;
  struct GNUNET_HashCode nkey;
  struct GNUNET_CRYPTO_AesSessionKey skey;
  struct GNUNET_CRYPTO_AesInitializationVector iv;
  struct GNUNET_HashCode query;
  ssize_t nsize;
  char ndata[DBLOCK_SIZE];
  char edata[DBLOCK_SIZE];
  const char *fn;
  struct GNUNET_DISK_FileHandle *fh;
  uint64_t off;
  struct IndexInfo *ii;

  if (size != sizeof (struct OnDemandBlock))
  {
    GNUNET_break (0);
    GNUNET_DATASTORE_remove (dsh, key, size, data, -1, -1,
                             GNUNET_TIME_UNIT_FOREVER_REL, &remove_cont, NULL);
    return GNUNET_SYSERR;
  }
  odb = (const struct OnDemandBlock *) data;
  off = GNUNET_ntohll (odb->offset);
  ii = GNUNET_CONTAINER_multihashmap_get (ifm, &odb->file_id);
  if (NULL == ii)
  {
    GNUNET_break (0);
    return GNUNET_SYSERR;
  }
  fn = ii->filename;
  if ((NULL == fn) || (0 != ACCESS (fn, R_OK)))
  {
    GNUNET_STATISTICS_update (GSF_stats,
                              gettext_noop
                              ("# index blocks removed: original file inaccessible"),
                              1, GNUNET_YES);
    GNUNET_DATASTORE_remove (dsh, key, size, data, -1, -1,
                             GNUNET_TIME_UNIT_FOREVER_REL, &remove_cont, NULL);
    return GNUNET_SYSERR;
  }
  if ((NULL ==
       (fh =
        GNUNET_DISK_file_open (fn, GNUNET_DISK_OPEN_READ,
                               GNUNET_DISK_PERM_NONE))) ||
      (off != GNUNET_DISK_file_seek (fh, off, GNUNET_DISK_SEEK_SET)) ||
      (-1 == (nsize = GNUNET_DISK_file_read (fh, ndata, sizeof (ndata)))))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                _
                ("Could not access indexed file `%s' (%s) at offset %llu: %s\n"),
                GNUNET_h2s (&odb->file_id), fn, (unsigned long long) off,
                (fn == NULL) ? _("not indexed") : STRERROR (errno));
    if (fh != NULL)
      GNUNET_DISK_file_close (fh);
    GNUNET_DATASTORE_remove (dsh, key, size, data, -1, -1,
                             GNUNET_TIME_UNIT_FOREVER_REL, &remove_cont, NULL);
    return GNUNET_SYSERR;
  }
  GNUNET_DISK_file_close (fh);
  GNUNET_CRYPTO_hash (ndata, nsize, &nkey);
  GNUNET_CRYPTO_hash_to_aes_key (&nkey, &skey, &iv);
  GNUNET_CRYPTO_aes_encrypt (ndata, nsize, &skey, &iv, edata);
  GNUNET_CRYPTO_hash (edata, nsize, &query);
  if (0 != memcmp (&query, key, sizeof (struct GNUNET_HashCode)))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_WARNING,
                _("Indexed file `%s' changed at offset %llu\n"), fn,
                (unsigned long long) off);
    GNUNET_DATASTORE_remove (dsh, key, size, data, -1, -1,
                             GNUNET_TIME_UNIT_FOREVER_REL, &remove_cont, NULL);
    return GNUNET_SYSERR;
  }
  GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
              "On-demand encoded block for query `%s'\n", GNUNET_h2s (key));
  cont (cont_cls, key, nsize, edata, GNUNET_BLOCK_TYPE_FS_DBLOCK, priority,
        anonymity, expiration, uid);
  return GNUNET_OK;
}