int main()
{
	char Message[255],c;
	while(1)
	{
		printf("Enter option: ");
		scanf("%c",&c);
		if(c=='c'||c=='d')
		{
			scanf("%c",&c);
			if(c==' ')
			{
				ReadString(Message);
				Encrypt(Message);
				printf("%s\n",Message);
			}
		}
		else if(c=='q') return 0;
	}
}