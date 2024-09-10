int main()
{
	//nb表示分组长度；nk表示密钥长度
	int i,nb,nk;
	char str[]="abcd1234567890123456789012345678901212345678901234567890123456789012";
    char key[32];
	char block[32];
	gentables();
	strtoHex(str,key);
	hextoStr(key,str);
	printf("Key=");
	for (i=0;i<64;i++)
		printf("%c",str[i]);
	printf("\n");
	for (i=0;i<32;i++)
		block[i]=i;
	for (nb=4;nb<=8;nb+=2)
		for (nk=4;nk<=8;nk+=2)
		{
			printf("\nBlock Size= %d bits, Key Size= %d bits\n",nb*32,nk*32);
			gkey(nb,nk,key);
			printf("Plain= ");
			for (i=0;i<nb*4;i++)
				printf("%02x",block[i]);
			printf("\n");
			//进行加密
			encrypt(block);
			//输出密文
			printf("Encrypt= ");
			for (i=0;i<nb*4;i++)
				printf("%02x",(unsigned char)block[i]);
			printf("\n");
			//进行解密
			decrypt(block);
			//输出明文
			printf("Decrypt= ");
			for (i=0;i<nb*4;i++)
				printf("%02x",block[i]);
			printf("\n");
		}
		system("pause");
		return 0;
}