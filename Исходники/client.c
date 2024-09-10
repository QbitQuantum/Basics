int main(){

	// printf("Testing RSA functions with EVP_DigestSign and EVP_DigestVerify\n");
	char response[1000];

	OpenSSL_add_all_algorithms();

	/* Sign and Verify HMAC keys */
	EVP_PKEY *skey = NULL, *vkey = NULL;
	
	int rc = make_keys(&skey, &vkey);
	assert(rc == 0);
	if(rc != 0)
	exit(1);

	assert(skey != NULL);
	if(skey == NULL)
	exit(1);

	assert(vkey != NULL);
	if(vkey == NULL)
	exit(1);
	DH *privkey=createPubkey();
	//char *dh_param_pub=BN_bn2dec(privkey->pub_key); 
	const byte *msg = BN_bn2dec(privkey->pub_key);//msg contains dh_param_pub
	printf("DH public key Generated:%s \n",msg);
	byte* sig = NULL;
	size_t slen = 0;

	
	
	sock=establishConnection();
	int i=0;
	//int count = split(data1, "$", tokens);
	sendMsg(sock,msg);
	
	 if( recv(sock, response , 6000 , 0) < 0)
	{
	puts("recv failed");
	}
	printf("Recieved Successfully:length of data=%d \n",(int)strlen(response));
	printf("DH public key Recieved:%s \n",response);
	//printf("Sent Successfully: length of data=%d\n",sumSend);
	char *pubkey=response;
	struct sec s=performDH(pubkey,privkey);
	printf("Shared key is:%s\n ",s.value);
	puts("The DH Key is");
	BIO_dump_fp(stdout, s.value, s.length);
	//free(msg);
	verifySignature(sock,msg);
	if(sig)
	OPENSSL_free(sig);

	if(skey)
	EVP_PKEY_free(skey);

	if(vkey)
	EVP_PKEY_free(vkey);
	
	return 0;
}