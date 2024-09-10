long get_limit()
{
	FILE* fp =	fopen(LIMIT_FILEPATH, "rb");
	if(NULL == fp)
	{
		printf("get limit : open tipslimit file failed\n");
		return -1;
	}
	char encrypted_text[BUF_LEN] = {0};
	fread(encrypted_text, BUF_LEN,1,fp);
	fclose(fp);
//	printf("Encrypted text is:%s\n", encrypted_text);
	char* pass = PASS;
	char* decrypted_text = encrypt(encrypted_text, pass);
//	printf("Decrypted text is:%s\n", decrypted_text);
	long num = atol(decrypted_text);
	free(decrypted_text);
	printf("get connection limit : %ld\n", num);
	return num;
}