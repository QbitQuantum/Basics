void main()
{
	try{
		cout <<"7.3/2.0 = " <<Div(7.3, 2.0) <<endl;
		cout <<"7.3/0.0 = " <<Div(7.3, 0.0) <<endl;
		cout <<"7.3/1.0 = " <<Div(7.3, 1.0) <<endl;
	}
	catch(double)
	{
		cout <<"发生除数为零的异常\n";
	}
	cout <<"程序执行成功\n";
}