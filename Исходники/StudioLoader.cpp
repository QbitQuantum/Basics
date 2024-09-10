bool LoadModel_Studio(FileSpecifier& Spec, Model3D& Model)
{
	ModelPtr = &Model;
	Model.Clear();
	
	Path = Spec.GetPath();
	logNote1("Loading 3D Studio Max model file %s",Path);
	
	OpenedFile OFile;
	if (!Spec.Open(OFile))
	{	
		logError1("ERROR opening %s",Path);
		return false;
	}
	
	ChunkHeaderData ChunkHeader;
	if (!ReadChunkHeader(OFile,ChunkHeader)) return false;
	if (ChunkHeader.ID != MASTER)
	{
		logError1("ERROR: not a 3DS Max model file: %s",Path);
		return false;
	}
	
	if (!ReadContainer(OFile,ChunkHeader,ReadMaster)) return false;
	
	if (Model.Positions.empty())
	{
		logError1("ERROR: no vertices found in %s",Path);
		return false;
	}
	if (Model.VertIndices.empty())
	{
		logError1("ERROR: no faces found in %s",Path);
		return false;
	}
	return true;
}