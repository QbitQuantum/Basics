int SquareRoom::ProcessInput()
{
	Welcome();


	std::cout << "You have found a" << " " << Object.Cstr() << std::endl;
	std::cout << "Type in a keyword to open the " << " " << Object.Cstr() << std::endl;
	String uInput;
	uInput.ReadFromConsole();
	uInput.ToLower();
	while (true)
	{

		if (uInput.Equalto("open"))
		{
			std::cout << "You win" << std::endl;
			system("pause");
			break;
		}
		else
		{
			std::cout << "Wrong keyword, try again" << std::endl;
			system("pause");

			uInput.ReadFromConsole();
			uInput.ToLower();


		}
		

	}

	return 0;

}