int main(int argc,char *argv[])
{
	
	
	int i=0,sys=0;
	int j;
	char arg1[100],arg2[100];
	if(argc==2)
	{
		for(i=0;argv[1][i]!='/';i++);
		for(j=0;j<i;j++)
		{
			arg1[j]=argv[1][j];
		}
		arg1[j]='\0';
		j=0;
		for(i++;argv[1][i]!='\0';i++)
		{
			arg2[j++]=argv[1][i];
		}
		arg2[j]='\0';
	}
	if(argc==3)
	{
		int check=2;
		for(i=0;argv[1][i]!='\0';i++)
		{
			if(argv[1][i]=='/')
			{
				check=1;
				break;
			}
		}
		if(check==1)
		{
			for(j=0;j<=i-1;j++)
			{
				arg1[j]=argv[1][j];
			}
			arg1[j]='\0';
		
			strcpy(arg2,argv[2]);
		}
		if(check==2)
		{
			strcpy(arg1,argv[1]);
			for(j=1;argv[2][j]!='\0';j++)
			{
				arg2[j-1]=argv[2][j];
			}
			arg2[j-1]='\0';
		
		
		}
	}
	if(argc==4)
	{
	strcpy(arg1,argv[1]);
	strcpy(arg2,argv[3]);
	}
	
		
		
	printf("%s %s\n",arg1,arg2);	
		
		
	
	//printf("args=%d\n",argc);
	pid_t pid;
	int p[2];//={open("pipe1",O_WRONLY),open("pipe2",O_RDONLY)};
	

	pipe(p);
	char filename1[100],filename2[100],path[100],descriptor[100];
	strcpy(path,"/proc/self/fd/");
	sprintf(descriptor, "%d", p[0]);
	strcat(path,descriptor);
	readlink(path, filename1, 100);
	printf("read end=%s path=%s\n",filename1,path);
	strcpy(path,"/proc/self/fd/");
	sprintf(descriptor, "%d", p[1]);
	strcat(path,descriptor);
	readlink(path, filename2, 100);
	printf("write end=%s  path=%s\n",filename2,path);
	pid=fork();
		if(pid==-1)
		{
			printf("error");
			exit(0);
		}
		else if(pid==0)
		{  
			pid=fork();
			
			if(pid==-1)
			{
				printf("error");
				exit(0);
			}
			else if(pid==0)
			{ 	
				close(p[1]);	
				printf("grandchild\n");
				//dup2(open(argv[i+1],O_RDONLY),0);
				dup2(p[0],0);
				//close(p[0]);
				execl(arg1,"",(char *)0);
			
				exit(0);
			}
			else
			{
				wait(&i);
				close(p[0]);
				printf("child\n");
				dup2(p[1],1);
			
				//dup2(open("pipe",O_WRONLY),1);
				execl(arg2,"",(char *)0);
			
				exit(0);
			}
			
		}
		else
		{
			printf("parent\n");
			wait(&i);
		}
		
	
	
		return 0;
}