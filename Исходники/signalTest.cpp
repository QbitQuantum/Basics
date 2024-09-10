int main()
{
	signal(SIGABRT, SignalHandler);
	signal(SIGTERM, SignalHandler);

	_onexit( exitfunc );

	int i = 0;

// 	while(1)
// 	{
// 		i ++ ;
// 	}
	_getch();
}