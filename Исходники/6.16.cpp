int main()
{
	double x;
	cout << fixed << setprecision( 0 );
	srand ( time ( 0 ) );
	for ( int count = 1; count <= 100; count++ )
	{
		x = -3 + rand() % 15;
		cout << x << endl;
	}

	return 0;
}