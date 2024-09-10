int pgp_keymgt(int force)
{
  FILE *f = NULL;
  BUFFER *key, *keybak, *userid, *out, *outkey, *outtxt, *pass, *secout;
  KEYRING *keys;
  int err = 0, res, recreate_pubring = 0, dsa_ok = 0;
#ifdef USE_IDEA
  int rsa_ok = 0;
#endif /* USE_IDEA */
  long expires;
  LOCK *seclock;

  key = buf_new();
  out = buf_new();
  keybak = buf_new();
  secout = buf_new();

  userid = buf_new();
  buf_sets(userid, REMAILERNAME);
  pass = buf_new();
  buf_sets(pass, PASSPHRASE);
  outtxt = buf_new();
  outkey = buf_new();

  /* We only want to build RSA keys if we also can do IDEA
   * This is to not lose any mail should users try our RSA key
   * with IDEA.
   */
#ifdef USE_IDEA
  /* FIXME: pgpdb_getky returns the expiration date from the last key in the keyring
   *        which probably works most of the time if the keys are in the correct order
   *        it doesn't return the latest expiration date (or 0) if the key in question
   *        is before another matching key in the keyring tho
   */
  res = pgpdb_getkey(PK_DECRYPT, PGP_ES_RSA, NULL, NULL, &expires, NULL, NULL,
				  NULL, NULL, NULL, pass);
  if (force == 2 || res < 0 || (expires > 0 && expires - KEYOVERLAPPERIOD < time(NULL))) {
    rsa_ok = -1;
    pgp_keygen(PGP_ES_RSA, 0, userid, pass, PGPKEY, PGPREMSECRING, 0);
  };

  if (force == 0 && (pgpdb_getkey(PK_ENCRYPT, PGP_ES_RSA, NULL, NULL, NULL, NULL, NULL,
				  NULL, NULL, PGPKEY, NULL) < 0) && rsa_ok == 0)
    rsa_ok = 1;
#endif /* USE_IDEA */
  /* FIXME: pgpdb_getky returns the expiration date from the last key in the keyring
   *        which probably works most of the time if the keys are in the correct order
   *        it doesn't return the latest expiration date (or 0) if the key in question
   *        is before another matching key in the keyring tho
   */
  res = pgpdb_getkey(PK_DECRYPT, PGP_E_ELG, NULL, NULL, &expires, NULL, NULL,
				  NULL, NULL, NULL, pass);
  if (force == 2 || res < 0 || (expires > 0 && expires - KEYOVERLAPPERIOD < time(NULL))) {
    dsa_ok = -1;
    pgp_keygen(PGP_E_ELG, 0, userid, pass, PGPKEY, PGPREMSECRING, 0);
  }

  if (force == 0 && (pgpdb_getkey(PK_ENCRYPT, PGP_E_ELG, NULL, NULL, NULL, NULL, NULL,
				  NULL, NULL, PGPKEY, NULL) > 0) && dsa_ok == 0)
    dsa_ok = 1;

  /* No need to rewrite the files - we didn't change a thing */
  if (
#ifdef USE_IDEA
      rsa_ok == 1 &&
#endif /* USE_IDEA */
      dsa_ok == 1)
    goto end;

  /* write keys one key per armor to make hand editing easy and old PGP
   * versions happy */
  err = -1;
  keys = pgpdb_open(PGPKEY, NULL, 0, PGP_TYPE_PUBLIC);
  if (keys == NULL)
    recreate_pubring = 1;
  else {
    while (pgpdb_getnext(keys, key, NULL, userid) != -1) {
      buf_clear(outtxt);
      if (pgp_makekeyheader(PGP_PUBKEY, key, outtxt, NULL, PGP_ANY) == 0) {
	err = 0;
	buf_appends(out, "Type Bits/KeyID     Date       User ID\n");
	buf_cat(out, outtxt);
	buf_nl(out);
	pgp_armor(key, PGP_ARMOR_KEY);
	buf_cat(out, key);
	buf_nl(out);
      }
    }
    pgpdb_close(keys);
  }
  if (err != 0)
    recreate_pubring = 1;
  err = -1;

  keys = pgpdb_open(PGPREMSECRING, NULL, 0, PGP_TYPE_PRIVATE);
  if (keys == NULL)
    goto end;
  while (pgpdb_getnext(keys, key, NULL, userid) != -1) {
    buf_clear(outtxt);
    buf_clear(outkey);
    buf_clear(keybak);
    buf_cat(keybak, key);
    if (pgp_makekeyheader(PGP_SECKEY, key, outtxt, pass, PGP_ANY) == 0) {
      err = 0;
      buf_appends(secout, "Type Bits/KeyID     Date       User ID\n");
      buf_cat(secout, outtxt);
      buf_nl(secout);
      pgp_armor(key, PGP_ARMOR_SECKEY);
      buf_cat(secout, key);
      buf_nl(secout);
    }
    buf_clear(outtxt);
    if (recreate_pubring &&
	pgp_makepubkey(keybak, outtxt, outkey, pass, PGP_ANY) == 0) {
      buf_appends(out, "Type Bits/KeyID     Date       User ID\n");
      buf_cat(out, outtxt);
      buf_nl(out);
      pgp_armor(outkey, PGP_ARMOR_KEY);
      buf_cat(out, outkey);
      buf_nl(out);
    }
  }
  pgpdb_close(keys);

  seclock = lockfile(PGPREMSECRING);
  if (err == 0 && (f = mix_openfile(PGPREMSECRING, "w")) != NULL) {
    buf_write(secout, f);
    fclose(f);
  } else
    err = -1;
  unlockfile(seclock);
  if (err == 0 && (f = mix_openfile(PGPKEY, "w")) != NULL) {
    buf_write(out, f);
    fclose(f);
  } else
    err = -1;
end:
  buf_free(key);
  buf_free(keybak);
  buf_free(out);
  buf_free(userid);
  buf_free(pass);
  buf_free(outtxt);
  buf_free(outkey);
  buf_free(secout);
  return (err);
}