/**
**  Save state of the dependencies to file.
**
**  @param file  Output file.
*/
void SaveUpgrades(CFile &file)
{
	file.printf("\n-- -----------------------------------------\n");
	file.printf("-- MODULE: upgrades\n\n");

	//
	//  Save the allow
	//
	for (std::vector<CUnitType *>::size_type i = 0; i < UnitTypes.size(); ++i) {
		file.printf("DefineUnitAllow(\"%s\", ", UnitTypes[i]->Ident.c_str());
		for (int p = 0; p < PlayerMax; ++p) {
			if (p) {
				file.printf(", ");
			}
			file.printf("%d", Players[p].Allow.Units[i]);
		}
		file.printf(")\n");
	}
	file.printf("\n");

	//
	//  Save the upgrades
	//
	for (std::vector<CUpgrade *>::size_type j = 0; j < AllUpgrades.size(); ++j) {
		file.printf("DefineAllow(\"%s\", \"", AllUpgrades[j]->Ident.c_str());
		for (int p = 0; p < PlayerMax; ++p) {
			file.printf("%c", Players[p].Allow.Upgrades[j]);
		}
		file.printf("\")\n");
	}
}