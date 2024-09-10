int dbaccess(char * server, char * user, char * cpw, RSA * rsa) {
	SQLHENV henv;
	SQLHDBC hdbc;
	char * pw;
	
	// Do something

    pw = base64_decode(cpw);	
	SQLConnect(hdbc, (SQLCHAR *)server, strlen(server), user, strlen(user), pw, strlen(pw)); // @violation WEAK_ENCRYPTION.PASSWORD
	
	RSA_private_decrypt(strlen(cpw), cpw, pw, rsa, RSA_PKCS1_PADDING);
	SQLConnect(hdbc, (SQLCHAR *)server, strlen(server), user, strlen(user), pw, strlen(pw));
	return 0;
}