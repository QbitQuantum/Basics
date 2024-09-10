/* Finalizes the digest context
 * Returns 1 if successful, 0 on failure or -1 on error
 */
int digest_context_finalize(
     digest_context_t *digest_context,
     digest_hash_t *digest_hash,
     size_t *size,
     liberror_error_t **error )
{
	static char *function = "digest_context_finalize";

	if( digest_context == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid digest context.",
		 function );

		return( -1 );
	}
	if( digest_hash == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid digest hash.",
		 function );

		return( -1 );
	}
	if( *size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBCRYPTO ) && defined( HAVE_OPENSSL_EVP_H )
	if( EVP_DigestFinal_ex(
	     digest_context,
	     (unsigned char *) digest_hash,
	     (unsigned int *) size ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to finalize digest hash.",
		 function );

		return( 0 );
	}
	if( EVP_MD_CTX_cleanup(
	     digest_context ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clean up digest context.",
		 function );
	}
#elif defined( HAVE_WINCPRYPT_H )
	if( digest_context->hash == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid digest context - missing hash.",
		 function );

		return( -1 );
	}
	if( CryptGetHashParam(
	     digest_context->hash,
	     HP_HASHVAL,
	     (BYTE *) digest_hash,
	     (DWORD *) size,
	     0 ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to finalize digest hash.",
		 function );

		return( 0 );
	}
	if( digest_context->crypt_provider != 0 )
	{
		CryptReleaseContext(
		 digest_context->crypt_provider,
		 0 );
	}
	if( digest_context->hash != 0 )
	{
		CryptDestroyHash(
		 digest_context->hash );
	}
#endif
	return( 1 );
}