void repeat ( int x, int y, int z )
{
	int a, b;
	string c, d;
	a = 1 + rand() % 4, b = 1 + rand() % 4;
	switch ( a )
	{
		case 1:
			c = "Very well";
			break;
		case 2:
			c = "Perfectly!"; 
			break;
		case 3:
			c = "Great job!";
			break;
		case 4:
			c = "Keep working in the same spirit!";
			break;
	}
	switch ( b )
	{
		case 1:
			d = "It's wrong! Try again!";
			break;
		case 2:
			d = "No. Please try again!";
			break;
		case 3:
			d = "Do not be discouraged!";
			break;
		case 4:
			d = "No. Continue your attempts!";
			break;
	}
	if ( z == x * y )
		cout << c << endl;
	else
	{
		cout << d << endl;
		cout << "What is " << x << " multiple by " << y << "?" << endl;
		cin >> z;
		repeat ( x, y, z );
	}
}