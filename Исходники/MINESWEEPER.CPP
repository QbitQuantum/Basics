void main()
{
	clrscr();
	int time;
	int i,j,k;
	clock_t tic=clock();
	cout<<"::MineSweeper::"<<endl;
	cout<<"\n Press ENTER to start the game.";
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			a[i][j]='.';
	getch();
	clock_t toc=clock();
	time=((toc-tic)*4)+3;
//	cout<<"\n Time= "<<time<<endl;
	place_mine(time);
	time=((toc-tic)*4)+3;
//	cout<<"\n Time= "<<time<<endl;
	place_1(time);
	time=((toc-tic)*7)+1;
//	cout<<"\n Time= "<<time<<endl;
	place_2(time);

//	for(i=0;i<10;i++)
//	{
//		if(i==0)
//			cout<<" ";
//		cout<<"  "<<i;
//	}
	cout<<endl;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
//			if(j==0)
//				cout<<i;
			cout<<"  "<<a[i][j];
		}
		cout<<endl;
	}

	for(i=0;i<10;i++)
	{
		cout<<bomb[i][0]<<" "<<bomb[i][1]<<"||";
	}
	getch();

	player();

	clrscr();
	cout<<"::MineSweeper::"<<endl;
	cout<<endl;
	for(i=0;i<10;i++)
	{
		if(i==0)
			cout<<" ";
		cout<<"  "<<i;
	}
	cout<<endl;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(j==0)
				cout<<i;
			cout<<"  "<<user[i][j];
		}
		cout<<endl;
	}
	cout<<"\n You took "<<f_count<<" chances";

	getch();
}