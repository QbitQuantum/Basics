/**
 * Get the namespace ID belonging to the given namespace name.
 *
 * @param cfg configuration to use
 * @param ns_uname unique (!) human-readable name for the namespace
 * @param nsid set to namespace ID based on 'ns_uname'
 * @return GNUNET_OK on success, GNUNET_SYSERR on failure
 */
int
GNUNET_PSEUDONYM_name_to_id (const struct GNUNET_CONFIGURATION_Handle *cfg,
    const char *ns_uname, struct GNUNET_HashCode * nsid)
{
  size_t slen;
  uint64_t len;
  unsigned int idx;
  char *name;
  struct GNUNET_HashCode nh;
  char *fn;
  struct GNUNET_DISK_FileHandle *fh;

  idx = -1;
  slen = strlen (ns_uname);
  while ((slen > 0) && (1 != SSCANF (&ns_uname[slen - 1], "-%u", &idx)))
    slen--;
  if (slen == 0)
    return GNUNET_SYSERR;
  name = GNUNET_strdup (ns_uname);
  name[slen - 1] = '\0';

  GNUNET_CRYPTO_hash (name, strlen (name), &nh);
  GNUNET_free (name);
  fn = get_data_filename (cfg, PS_NAMES_DIR, &nh);
  GNUNET_assert (fn != NULL);

  if ((GNUNET_OK != GNUNET_DISK_file_test (fn) ||
       (GNUNET_OK != GNUNET_DISK_file_size (fn, &len, GNUNET_YES, GNUNET_YES))) ||
      ((idx + 1) * sizeof (struct GNUNET_HashCode) > len))
  {
    GNUNET_free (fn);
    return GNUNET_SYSERR;
  }
  fh = GNUNET_DISK_file_open (fn,
                              GNUNET_DISK_OPEN_CREATE |
                              GNUNET_DISK_OPEN_READWRITE,
                              GNUNET_DISK_PERM_USER_READ |
                              GNUNET_DISK_PERM_USER_WRITE);
  GNUNET_free (fn);
  if (GNUNET_SYSERR ==
      GNUNET_DISK_file_seek (fh, idx * sizeof (struct GNUNET_HashCode),
			     GNUNET_DISK_SEEK_SET))
  {
    GNUNET_DISK_file_close (fh);
    return GNUNET_SYSERR;
  }
  if (sizeof (struct GNUNET_HashCode) !=
      GNUNET_DISK_file_read (fh, nsid, sizeof (struct GNUNET_HashCode)))
  {
    GNUNET_DISK_file_close (fh);
    return GNUNET_SYSERR;
  }
  GNUNET_DISK_file_close (fh);
  return GNUNET_OK;
}