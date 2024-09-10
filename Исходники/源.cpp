int main(int argc, char* argv[])
{
	string input;
	string output;

	int temp = 0;//判断是否有“-a”
	int i;

	Scan sca;
	Calculation calcul;

	for (i = 1; i < argc; i++)
	{
		input = argv[i];
		if (input == "-a")
		{
			temp = 1;
			continue;
		}

	}

	sca.ToStringQueue(input);
	queue<string>*q = sca.GetQueue();//定义队列指针接收队列

	//如果数字符合要求才运算 
	if (sca.m_ijudge == 0)
	{
		if (temp == 1)
		{
			cout << input << "= ";
		}
		calcul.trans(q);
		double result = calcul.count();
		cout << result << endl;

	}
	else
	{
		return 0;
	}

	system("pause");
	return 0;
}