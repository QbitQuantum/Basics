static int
testCreateFromFile ()
{
  struct GNUNET_CRYPTO_RsaPrivateKey *key;
  struct GNUNET_CRYPTO_RsaPublicKeyBinaryEncoded p1;
  struct GNUNET_CRYPTO_RsaPublicKeyBinaryEncoded p2;

  key = GNUNET_CRYPTO_rsa_key_create_from_file (KEYFILE);
  GNUNET_assert (NULL != key);
  GNUNET_CRYPTO_rsa_key_get_public (key, &p1);
  GNUNET_CRYPTO_rsa_key_free (key);
  key = GNUNET_CRYPTO_rsa_key_create_from_file (KEYFILE);
  GNUNET_assert (NULL != key);
  GNUNET_CRYPTO_rsa_key_get_public (key, &p2);
  GNUNET_assert (0 == memcmp (&p1, &p2, sizeof (p1)));
  GNUNET_CRYPTO_rsa_key_free (key);
  GNUNET_assert (0 == UNLINK (KEYFILE));
  key = GNUNET_CRYPTO_rsa_key_create_from_file (KEYFILE);
  GNUNET_assert (NULL != key);
  GNUNET_CRYPTO_rsa_key_get_public (key, &p2);
  GNUNET_assert (0 != memcmp (&p1, &p2, sizeof (p1)));
  GNUNET_CRYPTO_rsa_key_free (key);
  GNUNET_assert (0 == UNLINK (KEYFILE));
  return GNUNET_OK;
}