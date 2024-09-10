void writeTMatrixList( std::ofstream *outFile, std::vector<MMatrix>& transformMatrices, bool inverse, float scaleFactor)
{
	for( int matrixId = 0; matrixId < transformMatrices.size(); matrixId++)
	{
		MMatrix tm = transformMatrices[matrixId];
		if( inverse )
			tm = tm.inverse();

		if( matrixId == 0)
		{
			*outFile << "\t\tray_transform " << matrixToString(tm) << "\n"; // normal transform
		}
		else{
			*outFile << "\t\tray_mtransform " << matrixToString(tm) << "\n"; // motion transform
		}
	}
}