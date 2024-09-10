/**
**  Save state of the unit-type table to file.
**
**  @param file  Output file.
*/
void SaveUnitTypes(CFile &file)
{
	file.printf("\n--- -----------------------------------------\n");
	file.printf("--- MODULE: unittypes\n\n");

	// Save all stats
	for (std::vector<CUnitType *>::size_type i = 0; i < UnitTypes.size(); ++i) {
		const CUnitType &type = *UnitTypes[i];
		bool somethingSaved = false;

		for (int j = 0; j < PlayerMax; ++j) {
			if (Players[j].Type != PlayerNobody) {
				somethingSaved |= SaveUnitStats(type.Stats[j], type, j, file);
			}
		}
		if (somethingSaved) {
			file.printf("\n");
		}
	}
}