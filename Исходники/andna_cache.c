/*
 * lcl_destroy_keyring
 *
 * destroys accurately the keyring ^_^ 
 */
void
lcl_destroy_keyring(lcl_cache_keyring * keyring)
{
	if (keyring->priv_rsa)
		RSA_free(keyring->priv_rsa);
	if (keyring->pubkey)
		xfree(keyring->pubkey);
	if (keyring->privkey)
		xfree(keyring->privkey);

	setzero(keyring, sizeof(lcl_cache_keyring));
}