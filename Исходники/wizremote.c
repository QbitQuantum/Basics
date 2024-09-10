int aes_handshake(int socket, unsigned char *key)
{
	unsigned char expkey[4 * 4 * (10 + 1)];

	unsigned char token[TOKEN_SIZE];
	unsigned char enc[TOKEN_SIZE];
	unsigned char response[TOKEN_SIZE];
	int i;

	ExpandKey(key,expkey);

	for(i=0;i<TOKEN_SIZE;i++)
	{
		token[i] = rand()%255;
	}

	Encrypt(token, expkey, enc);

	//send token
	write(socket, enc, TOKEN_SIZE);

	//read response
	if(read_nbytes(socket, enc, TOKEN_SIZE) == 0)
		return 0;

	Decrypt(enc, expkey, response);

	//check response
	for(i=0;i<TOKEN_SIZE;i++)
	{
		if((response[i] ^ token_xor_key[i]) != token[i])
			return 0; 
	}

	return 1;
}