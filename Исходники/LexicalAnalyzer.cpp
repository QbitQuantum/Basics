int PreProcess(char *pcSubName)//预处理子程序，完成功能每次向ScanBuffer中装入固定字长的源程序代码
{
	static char fcFlag='L';
	int i;

	//将源程序中读入剔除空格注视等放到buffer
	char * pcCurrent=0;//只是当前要赋值的字节
	char ** ppcCurrent=&pcCurrent;//指向指针的指针
	char * pcStart;//指向数组的开始，计算偏移量用
	char * pcTemp;//临时变量，初始化用
	FILE * pfSourceFile;//指向要打开的源程序文件

	//初始化pcCurrent确认当前要装入的缓冲区
	if(fcFlag=='L') 
	{
		pcCurrent=acScanBufL;
		pcStart=acScanBufL;
	}
	else
	{
		pcCurrent=acScanBufR;
		pcStart=acScanBufR;
	}

	//初始化当前缓冲区为空字符
	pcTemp=pcCurrent;
	for(i=0;i<SBUFSIZE;i++)
	{
		*pcTemp=0;
		pcTemp++;
	}

	//打开文件
	pfSourceFile=fopen("test.txt","r");
	if(pfSourceFile==NULL) 
	{
		printf("The file %s was not opened\n",pcSubName);//判断文件打开是否成功
		exit(0);//装入失败退出
	}
	else//打开成功读入
	{
		if(fseek(pfSourceFile,lnOffset,SEEK_SET))//移动文件指针到应该的位置
		{
			perror("Fseek failed");
			exit(1);//移动光标失败退出
		}

		while((pcCurrent-pcStart)!=SBUFSIZE)//循环读入指定长度字符
		{
			char cTemp;//临时变量
			cTemp=fgetc(pfSourceFile);//读入一个字符
			cTemp=CheckChar(pfSourceFile,ppcCurrent,cTemp,'N');//获取一个合法的字符

			if(cTemp==0x20)
			{
				*pcCurrent=cTemp;
				pcCurrent++;
				*pcCurrent='#';//程序结束
				break;//判断是否到文件末尾
			}

			*pcCurrent=cTemp;//若刚才输入的不为空格也没结束则输入到缓冲区
			pcCurrent++;
		
		}	

		//修改偏移量为当前偏移量，为下次读入用
		lnOffset=ftell(pfSourceFile);
		
		//关闭文件
		fclose(pfSourceFile);

		//修改fcFlag为下次再次装入，更改缓冲区
		if(fcFlag=='L') fcFlag='R';
		else fcFlag='L';
	}

	return 3;
}