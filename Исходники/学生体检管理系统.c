unsigned int login(char *local_name,char *local_password)
{
	char user_name[16],user_password[16];
	char swap;
	int i,error = 0;
	system("mode con:cols=40 lines=15");
	while(1)
	{
		memset(user_name,'\0',sizeof(user_name));
		memset(user_password,'\0',sizeof(user_password));
		printf("\n\n\n\t\t管理员登陆\n\n\t*Tips:访 客 : anonymous");
		printf("\n  用户名：");
		for(i = 0;i < 15;i++)
		{
			swap=getchar();
			if(swap == '\n')
				break;
			else 
			{
				user_name[i] = swap;
			}
			
		}
		user_name[i]='\0';
		fflush(stdin);
		printf("\n  密  码：");
		for(i = 0;i < 15;i++)
		{
			swap = getch();
			if(swap == '\r'|| swap == '\n')
				break;
			else 
			{
				user_password[i] = swap;
				printf("*");
			}
			
		}
		user_password[i]='\0';
		system("cls");
		if(strcmp(user_password,local_password) != 0 || strcmp(user_name,local_name) !=0)
		{
			system("cls");
			printf("Warning: Error!-----用户名或密码错误！\n\t还可重试%d次***",2 - error);
			++error;
			if(error == 3)
			{
				printf("\n\n Warning!-----尝试次数已到!请等待3秒后再试");
				_sleep(2000);
				return FALSE;
			}
		}
		else
		{
			break;
		}
	} 
	return TURE;
}