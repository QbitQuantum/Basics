void sphere::SetupShape(void)
{
	Erase((2 * resolution + 1) * (resolution + 1), 4 * (resolution + 1) * resolution); 
	// To Do
	// 
	// Setup the data for a sphere

	float pi = 3.14159265358979323846f;

	/*
	Strips refer to the "columns" of the sphere,
	where as, rings, refer to the "rows" of the sphere.
	*/



	int longitudeLines = resolution + 1;
	int latitudeLines = resolution + 1;
	nVerts = longitudeLines*latitudeLines;
	int numTriangleVerts = resolution*resolution * 2 * 3;
	int currentVertexIdx = 0;
	float currentPhi = 0.0f;
	float phiIncrement = (pi / (float)(resolution));
	float currentTheta = 0.0f;
	float thetaIncrement = 2.0f * (pi / (float)(resolution));

	for (int i = 0; i < longitudeLines; i++) //for each strip
	{
		currentPhi = 0.0f; //reset Phi since its a new strip
		for (int j = 0; j < latitudeLines; j++) //for each ring
		{
			//Note: Each face has four vertices...which will be used to make 

			vertices[currentVertexIdx].position = point(cosf(currentTheta)*sinf(currentPhi), sinf(currentTheta)*sinf(currentPhi), cosf(currentPhi)) * radius;
			vertices[currentVertexIdx].normal = vector(cosf(currentTheta)*sinf(currentPhi), sinf(currentTheta)*sinf(currentPhi), cosf(currentPhi));
			if (IsZero(vertices[currentVertexIdx].normal)){
				vertices[currentVertexIdx].normal.Normalize();
			}

			currentVertexIdx++; //skip forward to next idx for new face
			currentPhi += phiIncrement;
		}

		currentTheta += thetaIncrement; //go to next strip
	}

	for (int i = 0; i < resolution; i++) //for each strip
	{

		for (int j = 0; j < resolution; j++) //for each ring
		{
			//Note: Each face has four vertices...which will be used to make 

			faces[nFaces].vertices[0] = j + (i*latitudeLines);
			faces[nFaces].vertices[1] = j + (i*latitudeLines) + 1;
			faces[nFaces++].vertices[2] = j + ((i + 1)*latitudeLines);

			faces[nFaces].vertices[0] = j + ((i + 1)*latitudeLines);
			faces[nFaces].vertices[1] = j + (i*latitudeLines) + 1;
			faces[nFaces++].vertices[2] = j + ((i + 1)*latitudeLines) + 1;

		}
	}
}