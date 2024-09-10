/*------------------------------------------------------------------------
 * Encrypt the user's cleartext password using the AES 128-bit (ECB)
 *  encryption algorithm.
 *
 *  @param session	The MXit session object
 *  @return			The encrypted & encoded password.  Must be g_free'd when no longer needed.
 */
char* mxit_encrypt_password( struct MXitSession* session )
{
	char			key[16 + 1];
	char			exkey[512];
	GString*		pass			= NULL;
	GString*		encrypted		= NULL;
	char*			base64;
	unsigned int	i;

	purple_debug_info( MXIT_PLUGIN_ID, "mxit_encrypt_password\n" );

	/* build the AES encryption key */
	g_strlcpy( key, INITIAL_KEY, sizeof( key ) );
	memcpy( key, session->clientkey, strlen( session->clientkey ) );
	ExpandKey( (unsigned char*) key, (unsigned char*) exkey );

	/* build the secret data to be encrypted: SECRET_HEADER + password */
	pass = g_string_new( SECRET_HEADER );
	g_string_append( pass, purple_connection_get_password( session->con ) );
	padding_add( pass );		/* add ISO10126 padding */

	/* now encrypt the secret. we encrypt each block separately (ECB mode) */
	encrypted = g_string_sized_new( pass->len );
	for ( i = 0; i < pass->len; i += 16 ) {
		char	block[16];

		Encrypt( (unsigned char*) pass->str + i, (unsigned char*) exkey, (unsigned char*) block );
		g_string_append_len( encrypted, block, 16 );
	}

	/* now base64 encode the encrypted password */
	base64 = purple_base64_encode( (unsigned char*) encrypted->str, encrypted->len );
	g_string_free( encrypted, TRUE );

	g_string_free( pass, TRUE );

	return base64;
}