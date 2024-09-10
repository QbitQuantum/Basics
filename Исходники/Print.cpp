//-----2 输出结果; 
void Print::Printanswer(string input)
{
	Calculate c;
	Scan s;
	double answer = 0;
	answer = c.Calculater(input);
	if (s.IsError() == true)
	{
		cout << "ERROR" << endl;
	}
	else
	{
		if (c.iserror() == false)
		{
			cout << answer << endl;
		}
		else
		{
			cout << "ERROR" << endl;
		}
	} 
	
}