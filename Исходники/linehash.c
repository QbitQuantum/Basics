/* 主程序：散列查找法 */
int main()
{
	int checked[50];   //检查数组
	int i,j,temp;
	long temptime;
	for(i = 0; i < MAX; i++)
	{
		hashtable[i] = BLANK;   //清除散列表
	}

	for(i = 0; i < 50; i++)
	{
		checked[i] = 0;   //清除检查数组
	}

	printf("散列表内容：\n");
	srand(time(&temptime) % 60);    //使用时间初始随机数
	i = 0;
	while(i != NUM)   //生成数组值的循环
	{
		temp = rand() % 50;   //随机数取值0 -49
		if(checked[temp] == 0)   //是否是已有的值
		{
			createtable(temp);    //创建散列表
			printf("%2d = >",temp);
			for(j = 0; j < MAX; j++)  //输出散列表
			{
				printf("[%2d]",hashtable[j]);
			}
			printf("\n");   
			checked[temp] = 1;   //设置此值生成过
			i++;				//下一个数组值
		}
	}

	while(1)  
	{
		printf("\n请输入查找值（0-49） ==>");
		scanf("%d",&temp);   //导入查找值
		if(temp != -1)
		{
			i = linehash(temp);   //调用散列查找
			if(i != -1)
			{
				printf("找到查找值：%d[%d]\n",temp,i);
			}
			else
			{
				printf("没有找到差好值：%d\n",temp);
			}
		}
		else
			exit(1);
	}

}