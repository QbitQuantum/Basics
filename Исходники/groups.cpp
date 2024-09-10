/**
**  Save groups.
**
**  @param file  Output file.
*/
void SaveGroups(CFile &file)
{
	file.printf("\n--- -----------------------------------------\n");
	file.printf("--- MODULE: groups\n\n");

	for (int g = 0; g < NUM_GROUPS; ++g) {
		file.printf("Group(%d, %d, {", g, Groups[g].NumUnits);
		for (int i = 0; i < Groups[g].NumUnits; ++i) {
			file.printf("\"%s\", ", UnitReference(*Groups[g].Units[i]).c_str());
		}
		file.printf("})\n");
	}
}