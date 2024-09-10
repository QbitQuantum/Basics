void CMapField::Save(CFile &file) const
{
	file.printf("  {%3d, %3d, %2d, %2d", tile, playerInfo.SeenTile, Value, cost);
	for (int i = 0; i != PlayerMax; ++i) {
		if (playerInfo.Visible[i] == 1) {
			file.printf(", \"explored\", %d", i);
		}
	}
	if (Flags & MapFieldHuman) {
		file.printf(", \"human\"");
	}
	if (Flags & MapFieldLandAllowed) {
		file.printf(", \"land\"");
	}
	if (Flags & MapFieldCoastAllowed) {
		file.printf(", \"coast\"");
	}
	if (Flags & MapFieldWaterAllowed) {
		file.printf(", \"water\"");
	}
	if (Flags & MapFieldNoBuilding) {
		file.printf(", \"mud\"");
	}
	if (Flags & MapFieldUnpassable) {
		file.printf(", \"block\"");
	}
	if (Flags & MapFieldWall) {
		file.printf(", \"wall\"");
	}
	if (Flags & MapFieldRocks) {
		file.printf(", \"rock\"");
	}
	if (Flags & MapFieldForest) {
		file.printf(", \"wood\"");
	}
#if 1
	// Not Required for save
	// These are required for now, UnitType::FieldFlags is 0 until
	// UpdateStats is called which is after the game is loaded
	if (Flags & MapFieldLandUnit) {
		file.printf(", \"ground\"");
	}
	if (Flags & MapFieldAirUnit) {
		file.printf(", \"air\"");
	}
	if (Flags & MapFieldSeaUnit) {
		file.printf(", \"sea\"");
	}
	if (Flags & MapFieldBuilding) {
		file.printf(", \"building\"");
	}
#endif
	file.printf("}");
}