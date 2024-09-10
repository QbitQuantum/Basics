void CResourceMapAnalyzer::SaveResourceMap() {
	std::string map = GetCacheFileName();
	FILE* saveFile = fopen(map.c_str(), "wb");

	assert(saveFile != NULL);

	fwrite(&NumSpotsFound, sizeof(int), 1, saveFile);
	fwrite(&AverageIncome, sizeof(float), 1, saveFile);

	for (int i = 0; i < NumSpotsFound; i++) {
		fwrite(&VectoredSpots[i], sizeof(float3), 1, saveFile);
	}

	fclose(saveFile);
}