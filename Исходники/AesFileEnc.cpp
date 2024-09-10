unsigned char * AesFileEnc::key ( )
{
	FILE* keystore;
	keystore = fopen(this->keystore_path, "r");
	unsigned char *iv = this->iv(32);
	unsigned char* key = new unsigned char[32];
	const char *prompt;
	prompt = getpass("Your password to keystore: " );
	unsigned char* sha;
   sha = SHA256(reinterpret_cast<const unsigned char*>(prompt), 32, NULL); //uwaga
   //printf("SHA %s aaa",(char *)sha);
	delete prompt;
	

  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);
  
	if(keystore == NULL)
	{
		keystore = fopen(this->keystore_path, "w+");
		std::cout<<this->keystore_path;
		srand(time(0));
		int j;
		char *buffer;
		buffer = new char;
		for(int i = 0 ; i<32; i++)
		{
			j = (int)(rand() / (RAND_MAX + 1.0) * 16);		
			sprintf(buffer,"%x",j);
			key[i] = *buffer;
		}
		 delete(buffer);

  unsigned char ciphertext[512];

  int ciphertext_len;

  ciphertext_len = this->encrypt (key, 32, sha, iv,
                            ciphertext);
	fprintf(keystore, "%s" ,(const char *)ciphertext);	
	//printf("KLUCZ zapisywany:%s KKK   %i" ,(const char *)ciphertext, ciphertext_len);	
}
else{

  unsigned char * decryptedtext = new unsigned char[512];
  unsigned char* keycipher = new unsigned char[512];
  int ciphertext_len = 0;
  int buff;
  while((buff = getc(keystore))!= EOF)
	{
		keycipher[ciphertext_len] = (unsigned char)buff;
		ciphertext_len++;
	}
	ciphertext_len--;
  //fscanf(keystore, "%512c", keycipher);
  int decryptedtext_len;
	//printf("KLUCZ wczytany:%s KKK   %i" ,(const char *)keycipher, ciphertext_len);	


  decryptedtext_len = decrypt(keycipher, ciphertext_len, sha, iv,
    decryptedtext);
  key = ( unsigned char *)decryptedtext;
}

  unsigned char* KEY;
  KEY = new unsigned char[this->keyLength];
  KEY[this->keyLength] = '\0';
  printf("%s        PIES \n",KEY);
  for(int i =0; i<this->keyLength; i++)
	{KEY[i] = key[i];}

  //delete(key);
  //delete(sha);
    	//std::cout << "tutajkhjghjfghyt" <<std::endl;
  fclose(keystore);
  //std::cout<<this->keyLength <<std::endl;
   //printf("KLUCZ %s",KEY);
  std::cout << (const char *)KEY<<"PIES"<<std::endl;
    std::cout <<key<<"PIES"<<std::endl;
   EVP_cleanup();
  ERR_free_strings();
  return KEY;
	}