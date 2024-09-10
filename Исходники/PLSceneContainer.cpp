/**
*  @brief
*    Returns a cell with the given name
*/
PLSceneCell *PLSceneContainer::GetCell(const String &sName, IGameNode &cIGameNode)
{
	// Check the given name
	if (!sName.GetLength())
		return nullptr; // Error!

	// First at all, IS there already a cell with this name?
	String sNameLower = sName;
	sNameLower.ToLower(); // Do ONLY use lower case, else the hashing will NOT return the same values!
	std::map<String, PLSceneCell*>::iterator pIterator = m_mapCells.find(sNameLower);
	if (pIterator != m_mapCells.end())
		return pIterator->second;

	// Nope, let's create a cell with this name
	g_pLog->LogFLine(PLLog::Scene, "Cell '%s' is created by the 3ds Max node '%s'", sName.GetASCII(), cIGameNode.GetName());
	PLSceneCell *pCell = new PLSceneCell(*this, sName);
	if (pCell) {
		// Register the new cell
		m_lstSceneNodes.push_back(pCell);
		m_mapCells.insert(std::make_pair(sNameLower, pCell));
		m_mapNodes.insert(std::make_pair(sNameLower, pCell));

		// Update the statistics
		m_sStatistics.nNumOfCells++;
		GetScene().m_sSceneStatistics.nNumOfCells++;
	}

	// Return the created cell
	return pCell;
}