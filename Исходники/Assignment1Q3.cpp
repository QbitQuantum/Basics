void main()	// main function
{
	int menu, result[100], total=0, count=0;
	char con;
	struct tm time;
		_getsystime(&time);
	int hr, min, sec;

	hr = time.tm_hour;
	min = time.tm_min;
	sec = time.tm_sec;

	int i=0;
	do
	{
		// Menu
		system("CLS");
		printf("_-_-_-_Menu_-_-_-_\n"
			   "[1] Multiplication\n"
			   "[2] Division\n"
			   "[3] Addition\n"
			   "[4] Subtraction\n"
			   "[5] Quit\n\n");

		printf("Choose a selection > ");
		scanf("%d",&menu);

		switch(menu)	// switch statement
		{
		case 1:
			{
				result[i] = Multiplication();	// function call Multiplication();
				output(result[i]);	// function call output();
				count++;	// the times of test
				break;
			}
		case 2:
			{
				result[i] = Division();	// function call Division();
				output(result[i]);	// function call output();
				count++;	// the times of test
				break;
			}
		case 3:
			{
				result[i] = Addition();	// function call Addition();
				output(result[i]);	// function call output();
				count++;	// the times of test
				break;
			}
		case 4:
			{
				result[i] = Subtraction();	// function call Subtraction();
				output(result[i]);	// function call output();
				count++;	// the times of test
				break;
			}
		case 5:
			{
				Quit(total,count,hr,min,sec);	// function call Quit();
				break;
			}
		default:
			{
				printf("Invalid Input! Please re-enter\n");
				main();	// re-run the main function
			}
			i++;
		}
		total = total + result[i];	// sum all the tests' marks
		// ask for user want to continue the test or not
		printf("Do you want to continue? (Y/N) ");
		fflush(stdin);
		scanf("%c",&con);
		toupper(con);
		while(con!='Y' && con!='N' && con!='y' && con!='n')
			{
				printf("Invalid Input! Please re-enter (Y/N)> ");
				fflush(stdin);
				scanf("%c",&con);
				toupper(con);
			}
	}while(con == 'Y' || con=='y');
	Quit(total,count,hr,min,sec);	// Print out the total result & Quit the program
}