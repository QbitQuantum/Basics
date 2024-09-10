cPiece::cVerticalStrategyPtr CreateVerticalStrategyFromString(const AString & a_StrategyDesc, bool a_LogWarnings)
{
	// Break apart the strategy class, the first parameter before the first pipe char:
	auto idxPipe = a_StrategyDesc.find('|');
	if (idxPipe == AString::npos)
	{
		idxPipe = a_StrategyDesc.length();
	}
	AString StrategyClass = a_StrategyDesc.substr(0, idxPipe);

	// Create a strategy class based on the class string:
	cPiece::cVerticalStrategyPtr Strategy;
	if (NoCaseCompare(StrategyClass, "Fixed") == 0)
	{
		Strategy = std::make_shared<cVerticalStrategyFixed>();
	}
	else if (NoCaseCompare(StrategyClass, "Range") == 0)
	{
		Strategy = std::make_shared<cVerticalStrategyRange>();
	}
	else if (NoCaseCompare(StrategyClass, "TerrainTop") == 0)
	{
		Strategy = std::make_shared<cVerticalStrategyTerrainTop>();
	}
	else if (NoCaseCompare(StrategyClass, "TerrainOrOceanTop") == 0)
	{
		Strategy = std::make_shared<cVerticalStrategyTerrainOrOceanTop>();
	}
	else
	{
		return nullptr;
	}

	// Initialize the strategy's parameters:
	AString Params;
	if (idxPipe < a_StrategyDesc.length())
	{
		Params = a_StrategyDesc.substr(idxPipe + 1);
	}
	if (!Strategy->InitializeFromString(Params, a_LogWarnings))
	{
		return nullptr;
	}

	return Strategy;
}