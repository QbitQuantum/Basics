// OpenSSL HMAC-SHA1 + Base64 エンコーディング
TEST( OAuthTest, HmacSha1Base64 )
{
	size_t resLength;
	unsigned char res[SHA_DIGEST_LENGTH + 1];

	char key[] = "1";
	int keyLength = strlen( key );

	unsigned char data[] = "012345";
	size_t dataLength = sizeof( data ) - 1;

	HMAC( EVP_sha1(), key, keyLength, data, dataLength, res, &resLength );

	char b64[256];
	DWORD b64Length;

	CryptBinaryToStringA( res, resLength, CRYPT_STRING_BASE64, b64, &b64Length );

	// 変換した文字列の最後に CRLF がついてくるのでそれをとる。
	char b64withoutCRLF[256];
	int b64length = strlen( b64 );
	for( int i=0; i<b64length-2; i++ )	// CRLF 分が -2
	{
		b64withoutCRLF[i] = b64[i];
	}
	b64withoutCRLF[b64length-2] = 0;	// null 文字
	
	// Python で作った値と比較。
	EXPECT_STREQ( "uSAq0a63u1W41eTdCrgbywm5CU8=", b64withoutCRLF );
}