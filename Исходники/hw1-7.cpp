int main( void )
{
	std::vector<int> priceTable = {
		1, 5, 8, 9, 10, 17, 17, 20, 24, 30
	};

	int len;
	printf_s( "input rod length : " );
	scanf_s( "%d", &len );

	printf_s( "MaxPrice : %d\n", GetMaxPrice( len, priceTable ) );

	getchar();
	getchar();
	return 0;
}