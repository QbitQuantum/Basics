void StatTracker::Reset( void )
{
	m_fTimePlayed						= 0;
	m_fBuildPhaseTime					= 0;
	m_fSurvivalTime						= 0;
	m_fDistanceWalked					= 0;
	m_fBloodSpilled						= 0;
	m_uGrenadesThrown					= 0;
	m_uTotalShotsFired					= 0;
	m_uMachineGunBullets				= 0;
	m_uShotgunShells					= 0;
	m_uRPGRounds						= 0;
	m_uHatTrickShots					= 0;
	m_uWallsPlaced						= 0;
	m_uWallsPickedUp					= 0;
	m_uWindowsPlaced					= 0;
	m_uWindowsPickedUp					= 0;
	m_uTowersBought						= 0;
	m_uTowersSold						= 0;
	m_uTrapsBought						= 0;
	m_uTrapsSold						= 0;
	m_uMoneySpent						= 0;
	m_uTotalKills						= 0;
	m_uRoundsSurvived					= 0;
	m_uConsecutiveRoundsSurvived		= 0;

	HRESULT hr;
	ostringstream stringstream;
	char path[MAX_PATH];
	LPWSTR wszPath = NULL;
	size_t size;

	// Get the path to the app data folder
	hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, 0, &wszPath);

	// Convert from LPWSTR to char[]
	wcstombs_s(&size, path, MAX_PATH, wszPath, MAX_PATH);

	// Convert char types
	if (hr == S_OK)
		stringstream << path;
	string pathtowrite = stringstream.str();

	// Add the company and game information
	pathtowrite += "\\RazorBalloon\\";

	// Create our directory
	SHCreateDirectoryEx(NULL, pathtowrite.c_str(), 0);

	// Create our save file
	pathtowrite += "stats.xml";

	Save(pathtowrite.c_str());
}