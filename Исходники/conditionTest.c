int main()
{
	int testCaseNo;

	Print("1 : CreateCondition System Call \n");
	Print("2: Wait Signal BroadCast System Call \n");
	Print("Enter your choice \n");
	testCaseNo = Scan();

	Print("\n\n");

	switch(testCaseNo)
	{
		case 1:
		{
			testCase1();
		}
		break;
		case 2:
		{
			testCase2();
		}
		break;
		default:
		{
			Print("Invalid Test Case No\n");
		}
		break;
	}
	/**
	 * Exit(0);
	 */

}