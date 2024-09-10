int main()
{
	char SourceString[THE_STRING_LENGTH] = "¡££¬¡¢£»£º£¿£¡¡­¡ª¡¤¡¥¡§0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789¡®¡¯¡°¡±¡©¡«¡¬¡Ã£¢¡Ã£§£à£ü¡¨¡²¡³¡´¡µ¡¶¡·¡¸¡¹¡º¡»£®¡¼¡½¡¾¡¿£¨£©£Û£Ý£û£ý";
	char TargetString[THE_STRING_LENGTH];
	printf("The Source String:%s\r\n", SourceString);

	Encrypt(SourceString, strlen(SourceString)+1, TargetString, strlen(SourceString)+1);
	printf("The Encrypt String:%s\r\n", TargetString);

	memset(SourceString, 0, sizeof(char)*THE_STRING_LENGTH);

	Decrypt(TargetString, strlen(TargetString)+1, SourceString, strlen(TargetString)+1);
	printf("The Decrypt Strng:%s\r\n", SourceString);
	getchar();


	return 0;
}