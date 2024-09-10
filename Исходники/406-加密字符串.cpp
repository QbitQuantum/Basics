int main()
{
	int i,n;
	char s[80],key[12],encrypt[80];              //输入串，密钥，加密后的串
	scanf("%s",key);
	getchar();                                            //吃掉输入密钥后的那个回车
	GeneAlphabet();                                  //产生字母表
	Reverse(key);                                       //将密钥key反转
	GetCharMap(key);                               //得到字母表的加密字符的对应表
	while(1)
	{
		gets(s);                                            //得到每行要加密的串
		if(strcmp(s,"#") == 0) break;            //如果输入#号则终止程序
		strcpy(encrypt,"");                            //将加密后的串先清空
		Encrypt(s,key,encrypt);                     //加密
		puts(encrypt);                                  //输出
	}
	return 0;
}