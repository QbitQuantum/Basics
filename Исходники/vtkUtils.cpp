/// @brief Apply a filter to each stream line
void runStreamLineThreshold(Options& opts, StringVector& args) {
	string inputStream = args[0];
	string inputSeeds = args[1];
	string outputStreamFile = args[2];
	string scalarName = opts.GetString("-scalarName");
	
	double lowThreshold = opts.GetStringAsReal("-thresholdMin", DBL_MIN);
	double highThreshold = opts.GetStringAsReal("-thresholdMax", DBL_MAX);
	
	vtkIO vio;
	vtkPolyData* streamLines = vio.readFile(inputStream);
	vtkPolyData* streamSeeds = vio.readFile(inputSeeds);
	
	vtkPolyData* outputStream = vtkPolyData::New();
	outputStream->SetPoints(streamLines->GetPoints());
	
	/// - Lookup SeedId and a given scalar array
	vtkDataArray* seedList = streamLines->GetCellData()->GetScalars("SeedId");
	vtkDataArray* seedScalars = streamSeeds->GetPointData()->GetScalars(scalarName.c_str());
	vtkCellArray* lines = vtkCellArray::New();
	vtkDoubleArray* filteredScalars = vtkDoubleArray::New();
	filteredScalars->SetName(scalarName.c_str());
	filteredScalars->SetNumberOfComponents(1);
	
	/// - Lookup a corresponding point scalar, apply threashold filter, and add to the new object
	for (int i = 0; i < seedList->GetNumberOfTuples(); i++) {
		int seedId = seedList->GetTuple1(i);
		double value = seedScalars->GetTuple1(seedId);
		
		if (lowThreshold <= value && value <= highThreshold) {
			lines->InsertNextCell(streamLines->GetCell(i));
			filteredScalars->InsertNextValue(value);
		}
	}
	
	outputStream->SetLines(lines);
	outputStream->GetCellData()->AddArray(filteredScalars);
	outputStream->BuildCells();
	outputStream->BuildLinks();
	
	vio.writeFile(outputStreamFile, outputStream);
}