int main(void)
{
	struct student stu;
	int i,sum=0;
	printf("please input the information:\n");
	printf("please input num:");
	scanf("%s",&stu.num);
	printf("please input name:");
	scanf("%s",&stu.name);
	printf("please input sex:");
	flushall();					//清除输入缓存区，以便正确输入性别
	scanf("%c",&stu.sex);
	printf("please input age:");
	scanf("%d",&stu.age);
	printf("please input birthday:");
	scanf("%d%d%d",&stu.birthday.year,&stu.birthday.month,&stu.birthday.day);
	printf("please input scores:");
	
	//循环输入该学生的三门成绩
	for (i=0; i<3; i++)
		scanf("%d",&stu.score[i]);
	
	//计算该学生三门成绩的总和
	for (i=0; i<3; i++)
		sum += stu.score[i];
	
	//计算该学生三门成绩的平均值
	stu.aver = sum / 3.0;
	printf("\nthe information is:");
	printf("\nthe num is %s",stu.num);
	printf("\nthe name is %s",stu.name);
	printf("\nthe sex is %c",stu.sex);
	printf("\nthe age is %d",stu.age);
	printf("\nthe birthday is %02d-%02d-%02d",stu.birthday.year,
			stu.birthday.month,stu.birthday.day);
	printf("\nthe score is:");
	for (i=0; i<3; i++)
		printf("%d ",stu.score[i]);
	printf("\nthe aver is %.2f\n",stu.aver);
}