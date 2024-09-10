int main()
{
	SetConsoleOutputCP(1251);
	A.x = 65;
	B.x = 90;
	
	cout << "Тип элементов:\n 1 - int\n 2 - double\n 3 - char\n";
	cin >> x;
	if( x < 1 || x > 3 )
	{
		cout << "Указано неверное значение типа элемента.";
		_getch();
		return 0;
	}
	cout << "Количество элементов: ";
	cin >> N;
	if( N < 1 )
	{
		cout << "Количеcтво элементов не может быть отрицательным!Попробуйте еще раз.";
		_getch();
		return 0;
	}
	if( x != 3 )
	{
		cout << "Промежуток (a,b): ";
		if( x == 2 )
		{
			cin >> A.y >> B.y;
		}