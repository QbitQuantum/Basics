void main()
{
	old=getvect(0x1C);//得到中断向量
	setvect(0x1C,get);//设置中断向量
	gettime(&t);//获取时间
	PrintClock();//显示时间
	while(1)
	{
		Clock();
		UpdateClock();//更新显示
		End();
	}

}