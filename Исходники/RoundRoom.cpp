int RoundRoom::ProcessInput()
{
	Welcome();
	findKey();
	String uInput;
	uInput.ReadFromConsole();
	uInput.ToLower();

	if (uInput.Equalto("back"))
	{
		std::cout << "Valid " << std::endl;
		return 0;
	}
	else
	{

		std::cout << "Dead end, try again" << std::endl;
		system("pause");
		return roomID;
	}
	return roomID;
}