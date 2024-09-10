//================================================================================================================
vector<string> CGlobal::GetAvailableDrives()
{
	DWORD bitmask = GetLogicalDrives();

	vector<string> drivesAvailable;
	vector<string> driveList;

	//Can add the rest of the alphabet.
	driveList.push_back("a:");
	driveList.push_back("b:");
	driveList.push_back("c:");
	driveList.push_back("d:");
	driveList.push_back("e:");
	driveList.push_back("f:");
	driveList.push_back("g:");
	driveList.push_back("h:");
	driveList.push_back("i:");

	for (int i = 0; i < driveList.size(); i++)
	{
		string drive = driveList[i];

		if ((bitmask & (1 << i)) == 0) //Shift bitmask and if 0 drive is free
		{
			// Free and does not exist in the system
		}
		else
		{
			drivesAvailable.push_back(drive);
		}
	}

	return drivesAvailable;
}