void AlgorithmVoronoiFields<T>::CreateTotalDistrict(const Map2D<T> &OriginalMap, const DistrictMap &OriginalDistrictData, const POS_2D &GlobalStartPos, const T &CutOffValue, const ALGORITHM_VORONOI_FIELDS::OCCUPATION_MAP::CELL_TYPE &OccupationLevel, ALGORITHM_VORONOI_FIELDS::DISTRICT_SIZE &DistrictSize, ALGORITHM_VORONOI_FIELDS::ID_MAP &IDMap, ALGORITHM_VORONOI_FIELDS::OCCUPATION_MAP &OccupationMap)
{
	std::queue<POS_2D> posToCheck;

	posToCheck.push(GlobalStartPos);
	do
	{
		for(const auto &navOption : NavigationOptions)
		{
			const POS_2D adjacentGlobalPos = posToCheck.front() + navOption;
			const POS_2D adjacentLocalPos = OriginalDistrictData.ConvertToLocalPosition(adjacentGlobalPos);

			DistrictMap::CELL_TYPE inDistrict;
			if(OriginalDistrictData.GetPixel(adjacentLocalPos, inDistrict) < 0 || inDistrict != DISTRICT_MAP::IN_DISTRICT)
				continue;		// Skip if not in district

			if(IDMap.GetPixel(adjacentLocalPos) != ALGORITHM_VORONOI_FIELDS::INVALID_ID)
				continue;		// Skip if already checked

			// Check if adjacent cell has same occuptation level
			const ALGORITHM_VORONOI_FIELDS::OCCUPATION_MAP::CELL_TYPE adjacentOccupationLevel = IsOccupiedCell(OriginalMap.GetPixel(adjacentGlobalPos), CutOffValue);
			if(OccupationLevel == adjacentOccupationLevel)
			{
				// Add this position to district
				IDMap.SetPixel(adjacentLocalPos, DistrictSize.DistrictID);
				OccupationMap.SetPixel(adjacentLocalPos, OccupationLevel);
				DistrictSize.ComparePos(adjacentGlobalPos);

				posToCheck.push(adjacentGlobalPos);
			}
		}

		posToCheck.pop();
	}
	while(posToCheck.size() > 0);
}