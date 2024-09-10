/* Long-term passwords are computed over the key:

            key = MD5(username ":"******":" SASLprep(password))

   Per RFC 5389 S 15.4
*/
int
nr_stun_compute_lt_message_integrity_password(const char *username, const char *realm,
                                              Data *password, Data *hmac_key)
{
  char digest_input[1000];
  int i;
  int r, _status;
  size_t len;

  /* First check that the password is ASCII. We are supposed to
     SASLprep but we don't support this yet
     TODO([email protected]): Add SASLprep for password.
 */
  for (i=0; i<password->len; i++) {
    if (!__isascii(password->data[i]))
      ABORT(R_BAD_DATA);
  }

  if (hmac_key->len < 16)
    ABORT(R_BAD_ARGS);

  snprintf(digest_input, sizeof(digest_input), "%s:%s:", username, realm);
  if ((sizeof(digest_input) - strlen(digest_input)) < password->len)
    ABORT(R_BAD_DATA);

  len = strlen(digest_input);
  memcpy(digest_input + len, password->data, password->len);


  if (r=nr_crypto_md5((UCHAR *)digest_input, len + password->len, hmac_key->data))
    ABORT(r);
  hmac_key->len=16;

  _status=0;
abort:
  return(_status);
}