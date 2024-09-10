void Tile::prepareDraw(Generator* generator)
{
	float delta = this->size / (this->pointsCount - 2);
	float startX = (this->xCoord * this->size) - (this->size / 2.0f);
	float startZ = (this->zCoord * this->size) - (this->size / 2.0f);

	float* vertexData = new float[vertexCount * 3];
	unsigned int* indexData = new unsigned int[indexCount];
	float* normalData = new float[vertexCount * 3];
	float* colourData = new float[vertexCount * 4];

	//Vertex Buffer:
	for(unsigned int row = 0; row < this->pointsCount - 1; row++)
	{
		for(unsigned int col = 0; col < this->pointsCount - 1; col++)
		{
			//Set X:
			vertexData[vertexBufferIndex(row, col, 0)] = startX + delta * col;

			//Set Y:
			vertexData[vertexBufferIndex(row, col, 1)] = this->points[row][col];

			//Set Z:
			vertexData[vertexBufferIndex(row, col, 2)] = startZ + delta * row;
		}
	}

	bool flip = true;
	int index = 0;
	//Index Buffer
	for(unsigned int row = 0; row < this->pointsCount - 2; row++)
	{
		for(unsigned int col = 0; col < this->pointsCount - 2; col++)
		{
			if(flip)
			{
				//Build Top Left Triangle:
				indexData[index++] = indexBufferIndex(row + 0, col + 0);
				indexData[index++] = indexBufferIndex(row + 1, col + 0);
				indexData[index++] = indexBufferIndex(row + 0, col + 1);

				//Build Bottom Right Triangle:
				indexData[index++] = indexBufferIndex(row + 1, col + 0);
				indexData[index++] = indexBufferIndex(row + 1, col + 1);
				indexData[index++] = indexBufferIndex(row + 0, col + 1);
			}
			else
			{
				//Build Top Right Triangle:
				indexData[index++] = indexBufferIndex(row + 0, col + 0);
				indexData[index++] = indexBufferIndex(row + 1, col + 1);
				indexData[index++] = indexBufferIndex(row + 0, col + 1);

				//Build Bottom Left Triangle:
				indexData[index++] = indexBufferIndex(row + 0, col + 0);
				indexData[index++] = indexBufferIndex(row + 1, col + 0);
				indexData[index++] = indexBufferIndex(row + 1, col + 1);
			}

			flip = !flip;
		}

		flip = !flip;
	}

	//Normal Buffer:
	if(Util::Config::convertSettingToBool("render", "smooth_shading"))
	{
		//Smooth Shading:
		Math::Vector3f currentPoint = Math::Vector3f();
		Math::Vector3f edgeOne = Math::Vector3f();
		Math::Vector3f edgeTwo = Math::Vector3f();
		
		for(unsigned int row = 0; row < this->pointsCount - 1; row+=2)
		{
			for(unsigned int col = 0; col < this->pointsCount - 1; col+=2)
			{
				//Set Current Point
				currentPoint.x = startX + (delta * col);
				currentPoint.y = this->points[row][col];
				currentPoint.z = startZ + (delta * row);

				//Set Up Point:
				edgeOne.x = currentPoint.x;
				edgeOne.y = this->points[row + 1][col];
				edgeOne.z = currentPoint.z + delta;

				//Set Right Point:
				edgeTwo.x = currentPoint.x + delta;
				edgeTwo.y = this->points[row][col + 1];
				edgeTwo.z = currentPoint.z;

				//Create Edge Vectors:
				edgeOne.subtract(&currentPoint);
				edgeTwo.subtract(&currentPoint);

				edgeOne.crossProduct(&edgeTwo);
				edgeOne.normalize();

				//Starting Point
				normalData[vertexBufferIndex(row, col, 0)] = edgeOne.x;
				normalData[vertexBufferIndex(row, col, 1)] = edgeOne.y;
				normalData[vertexBufferIndex(row, col, 2)] = edgeOne.z;

				//Right Point:
				if(col + 1 < this->pointsCount - 1)
				{
					normalData[vertexBufferIndex(row, col + 1, 0)] = edgeOne.x;
					normalData[vertexBufferIndex(row, col + 1, 1)] = edgeOne.y;
					normalData[vertexBufferIndex(row, col + 1, 2)] = edgeOne.z;
				}

				//Top Point:
				if(row + 1 < this->pointsCount - 1)
				{
					normalData[vertexBufferIndex(row + 1, col, 0)] = edgeOne.x;
					normalData[vertexBufferIndex(row + 1, col, 1)] = edgeOne.y;
					normalData[vertexBufferIndex(row + 1, col, 2)] = edgeOne.z;
				}
			}
		}

		for(unsigned int row = 1; row < this->pointsCount - 1; row+=2)
		{
			for(unsigned int col = 1; col < this->pointsCount - 1; col+=2)
			{
				//Set Current Point
				currentPoint.x = startX + (delta * col);
				currentPoint.y = this->points[row][col];
				currentPoint.z = startZ + (delta * row);

				//Set Up Point:
				edgeOne.x = currentPoint.x;
				edgeOne.y = this->points[row + 1][col];
				edgeOne.z = currentPoint.z + delta;

				//Set Right Point:
				edgeTwo.x = currentPoint.x + delta;
				edgeTwo.y = this->points[row][col + 1];
				edgeTwo.z = currentPoint.z;

				//Create Edge Vectors:
				edgeOne.subtract(&currentPoint);
				edgeTwo.subtract(&currentPoint);

				edgeOne.crossProduct(&edgeTwo);
				edgeOne.normalize();

				//Starting Point
				normalData[vertexBufferIndex(row, col, 0)] = edgeOne.x;
				normalData[vertexBufferIndex(row, col, 1)] = edgeOne.y;
				normalData[vertexBufferIndex(row, col, 2)] = edgeOne.z;

				//Right Point:
				if(col + 1 < this->pointsCount - 1)
				{
					normalData[vertexBufferIndex(row, col + 1, 0)] = edgeOne.x;
					normalData[vertexBufferIndex(row, col + 1, 1)] = edgeOne.y;
					normalData[vertexBufferIndex(row, col + 1, 2)] = edgeOne.z;
				}

				//Top Point:
				if(row + 1 < this->pointsCount - 1)
				{
					normalData[vertexBufferIndex(row + 1, col, 0)] = edgeOne.x;
					normalData[vertexBufferIndex(row + 1, col, 1)] = edgeOne.y;
					normalData[vertexBufferIndex(row + 1, col, 2)] = edgeOne.z;
				}
			}
		}
	}
	else //Flat Shading
	{
		Math::Vector3f currentPoint = Math::Vector3f();
		Math::Vector3f edgeOne = Math::Vector3f();
		Math::Vector3f edgeTwo = Math::Vector3f();

		for(unsigned int row = 0; row < this->pointsCount - 1; row++)
		{
			for(unsigned int col = 0; col < this->pointsCount - 1; col++)
			{
				//Set Current Point
				currentPoint.x = startX + (delta * col);
				currentPoint.y = this->points[row][col];
				currentPoint.z = startZ + (delta * row);

				//Set Up Point:
				edgeOne.x = currentPoint.x;
				edgeOne.y = this->points[row + 1][col];
				edgeOne.z = currentPoint.z + delta;

				//Set Right Point:
				edgeTwo.x = currentPoint.x + delta;
				edgeTwo.y = this->points[row][col + 1];
				edgeTwo.z = currentPoint.z;

				//Create Edge Vectors:
				edgeOne.subtract(&currentPoint);
				edgeTwo.subtract(&currentPoint);

				edgeOne.crossProduct(&edgeTwo);
				edgeOne.normalize();

				//Set X:
				normalData[vertexBufferIndex(row, col, 0)] = edgeOne.x;

				//Set Y:
				normalData[vertexBufferIndex(row, col, 1)] = edgeOne.y;

				//Set Z:
				normalData[vertexBufferIndex(row, col, 2)] = edgeOne.z;
			}
		}
	}

	//Colour Buffer:
	index =  0;
	Math::Vector3f vertexPosition = Math::Vector3f();
	Biome* biomes[2];
	int regionCoords[2];
	float distances[2];

	float halfTransitionSize = generator->transitionSize / 2.0f;

	Math::Vector3f one = Math::Vector3f();
	Math::Vector3f two = Math::Vector3f();
	Math::Vector3f pPrime = Math::Vector3f();

	float L2 = 0.0f;
	float t = 0.0f;
	float diff = 0.0f;
	float dOne = 0.0f;
	float dTwo = 0.0f;

	for(unsigned int row = 0; row < this->pointsCount - 1; row++)
	{
		for(unsigned int col = 0; col < this->pointsCount - 1; col++)
		{
			regionCoords[0] =  (int)((startX + delta * col)/ generator->regionSize);
			regionCoords[1] =  (int)((startZ + delta * row)/ generator->regionSize);

			vertexPosition.x = vertexData[vertexBufferIndex(row, col, 0)];
			vertexPosition.y = 0.0f;
			vertexPosition.z = vertexData[vertexBufferIndex(row, col, 2)];

			generator->getClosestCornerBiome(regionCoords, &vertexPosition, biomes, distances);

			L2 = biomes[0]->position->distanceSquared(biomes[1]->position);

			one = Math::Vector3f(&vertexPosition);
			two = Math::Vector3f(biomes[1]->position);

			one.subtract(biomes[0]->position);
			two.subtract(biomes[0]->position);

			t = one.dotProduct(&two) / L2;

			pPrime = Math::Vector3f(biomes[1]->position);
			pPrime.subtract(biomes[0]->position);
			pPrime.scale(t);
			pPrime.add(biomes[0]->position);

			dOne = pPrime.distance(biomes[0]->position);
			dTwo = pPrime.distance(biomes[1]->position);

			diff = abs(dOne - dTwo);

			/*if(diff <= halfTransitionSize)
			{
				float factor = (diff + halfTransitionSize) / generator->transitionSize;

				if(dOne <= dTwo)
				{
					colourData[index++] = factor * biomes[0]->colour[0] + (1.0f - factor) * biomes[1]->colour[0];
					colourData[index++] = factor * biomes[0]->colour[1] + (1.0f - factor) * biomes[1]->colour[1];
					colourData[index++] = factor * biomes[0]->colour[2] + (1.0f - factor) * biomes[1]->colour[2];
					colourData[index++] = factor * biomes[0]->colour[3] + (1.0f - factor) * biomes[1]->colour[3];
				}
				else
				{
					colourData[index++] = factor * biomes[1]->colour[0] + (1.0f - factor) * biomes[0]->colour[0];
					colourData[index++] = factor * biomes[1]->colour[1] + (1.0f - factor) * biomes[0]->colour[1];
					colourData[index++] = factor * biomes[1]->colour[2] + (1.0f - factor) * biomes[0]->colour[2];
					colourData[index++] = factor * biomes[1]->colour[3] + (1.0f - factor) * biomes[0]->colour[3];
				}

				colourData[index++] = 1.0f;
				colourData[index++] = 1.0f;
				colourData[index++] = 1.0f;
				colourData[index++] = 1.0f;
			}
			else*/
			{
				colourData[index++] = biomes[0]->colour[0];
				colourData[index++] = biomes[0]->colour[1];
				colourData[index++] = biomes[0]->colour[2];
				colourData[index++] = biomes[0]->colour[3];
			}
		}
	}


	//Delete the Old Buffers(if there are any)
	this->deleteBuffers();

	//Create Buffers
	glGenBuffers(BUFFERCOUNT, bufferIDs);

	//Vertex Buffer:
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 3, vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] vertexData;

	//Index Buffer:
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIDs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete[] indexData;

	//Normal Buffer:
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[2]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 3, normalData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] normalData;

	//Colour Buffer:
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[3]);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 4, colourData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] colourData;

	this->hasBuffers = true;

	//std::cout << "Vertex Count: " << (this->vertexCount * 3)<< std::endl;
	//std::cout << "Index Count: " << this->indexCount << std::endl;
}