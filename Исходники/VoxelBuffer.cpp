VoxelBuffer * VoxelBuffer::factory(const string& filename)
{
	ifstream fin(filename);
	string inputBuffer;
	VoxelBuffer * tempBuffer;

	fin >> inputBuffer;		// "DELT"
	fin >> inputBuffer;		// Delta value
	float delta = (float)atof(inputBuffer.c_str());

	fin >> inputBuffer;		// "XYZC"
	fin >> inputBuffer;
	ivec3 dimensions;
	dimensions.x = atoi(inputBuffer.c_str());
	fin >> inputBuffer;
	dimensions.y = atoi(inputBuffer.c_str());
	fin >> inputBuffer;
	dimensions.z = atoi(inputBuffer.c_str());

	tempBuffer = new VoxelBuffer(delta, dimensions);
	float tempDensity/*, tempLight*/;		// Omit reading in lights temporarily
	voxel tempVoxel;
	int voxelBufferSize = dimensions.x * dimensions.y * dimensions.z;
	tempBuffer->voxels = new voxel[voxelBufferSize];
	int i = 0;

	// Read in voxel densities (and lights...later)
	while (!fin.eof()) {
		fin >> inputBuffer;
		tempDensity = (float)atof(inputBuffer.c_str());
		tempVoxel.density = tempDensity;
		tempVoxel.light = -1.0;
		tempBuffer->voxels[i++] = tempVoxel;	// Add voxel to the 1D array
	}

	return tempBuffer;
}