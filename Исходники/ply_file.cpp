GLuint Model_PLY::LoadFlat(GLchar* filename)
{
	char* pch = strstr(filename, ".ply");

	if (pch != nullptr)
	{
		// Open file and read it.
		FILE* file;
		fopen_s(&file, filename, "rb");

		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file); //ftell is get the current position of pointer.

		try
		{
			vertexBuffer = (float*)malloc(fileSize);
		}
		catch (char*) // but why should be char* here?
		{
			return -1;
		}

		if (vertexBuffer == nullptr)
		{
			return -1;
		}

		fseek(file, 0, SEEK_SET);

		faceTriangles = (float*)malloc(fileSize * sizeof(float));
		verticesNormals = (float*)malloc(fileSize * sizeof(float));

		if (file != nullptr)
		{
			int i = 0;
			int temp = 0;
			int normalIndex = 0;
			int triangleIndex = 0;
			char buffer[1000]; // every time gets 1000 buffer.

			fgets(buffer, 300, file); //ply

			// READ HEADER
			//-------------------

			// Find number of vertexes
			// e.g. element vertex 12
			while (strncmp("element vertex", buffer, strlen("element vertex")) != 0)
			{
				fgets(buffer, 300, file);
			}
			strcpy_s(buffer, sizeof(buffer) - strlen("element vertex"), buffer + strlen("element vertex")); //erase "element vertex" header.
			sscanf_s(buffer, "%i", &this->numConnectedPoints); //read integer value for num of points.
			std::cout << "Number of connected point is : " << numConnectedPoints << std::endl;

			// find number of faces
			// e.g. element face 10
			fseek(file, 0, SEEK_SET);
			while (strncmp("element face", buffer, strlen("element face")) != 0)
			{
				fgets(buffer, 300, file);
			}
			strcpy_s(buffer, sizeof(buffer) - strlen("element face"), buffer + strlen("element face")); //erase "element face" header.
			sscanf_s(buffer, "%i", &this->numFaces); //read integer value for num of faces.
			std::cout << "Number of faces is : " << numFaces << std::endl;

			// go to end_header
			while (strncmp(("end_header"), buffer, strlen("end_header")) != 0)
			{
				fgets(buffer, 300, file);
			}


			// Read vertexes
			i = 0;
			for (GLuint iter = 0; iter < this->numConnectedPoints; ++iter)
			{
				fgets(buffer, 300, file);

				sscanf_s(buffer, "%f %f %f", &vertexBuffer[i], &vertexBuffer[i + 1], &vertexBuffer[i + 2]);
				i += 3;
			}

			// Read faces
			i = 0;
			for (GLuint iter = 0; iter < this->numFaces; ++iter)
			{
				fgets(buffer, 300, file);

				if ('3' == buffer[0])
				{
					int vert0 = 0, vert1 = 0, vert2 = 0;
					buffer[0] = ' ';
					sscanf_s(buffer, "%i%i%i", &vert0, &vert1, &vert2);




					// set values to faceTriangles.
 					faceTriangles[triangleIndex] = vertexBuffer[3 * vert0];
 					faceTriangles[triangleIndex + 1] = vertexBuffer[3 * vert0 + 1];
					faceTriangles[triangleIndex + 2] = vertexBuffer[3 * vert0 + 2];
 					faceTriangles[triangleIndex + 3] = vertexBuffer[3 * vert1];
					faceTriangles[triangleIndex + 4] = vertexBuffer[3 * vert1 + 1];
					faceTriangles[triangleIndex + 5] = vertexBuffer[3 * vert1 + 2];
 					faceTriangles[triangleIndex + 6] = vertexBuffer[3 * vert2];
					faceTriangles[triangleIndex + 7] = vertexBuffer[3 * vert2 + 1];
					faceTriangles[triangleIndex + 8] = vertexBuffer[3 * vert2 + 2];
 
 					// going to calculate verticesNormals.
					vec3 point0(vertexBuffer[3 * vert0], vertexBuffer[3 * vert0 + 1], vertexBuffer[3 * vert0 + 2]);
					vec3 point1(vertexBuffer[3 * vert1], vertexBuffer[3 * vert1 + 1], vertexBuffer[3 * vert1 + 2]);
					vec3 point2(vertexBuffer[3 * vert2], vertexBuffer[3 * vert2 + 1], vertexBuffer[3 * vert2 + 2]);
 
 					vec3 norm(0.0f);
 					this->calculateNormal(point0, point1, point2, norm);

 					for (int offset = 0; offset < 9; ++offset)
 					{
						verticesNormals[normalIndex + offset] = norm[offset % 3]; //set normal for each point.
 					}
 
 					normalIndex += 9; //set offset to next triangle. 

					triangleIndex += 9; //set offset to next triangle.
					numConnectedTriangles += 3; // three points per triangle
				}
				i += 3;
			}

			fclose(file);

		}
		else
		{
			std::cerr << "Error : Can not open file." << std::endl;
		}
	}
	else
	{
		std::cerr << "Error : File do not have a \".ply\" extension." << std::endl;
	}
	return 0;
}