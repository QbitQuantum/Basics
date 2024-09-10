bool ModelClass::LoadCylinder(float Radius, float Height, int numRSlice, int numVSlice, float texScale)
{
	m_vertexCount = 6 * ((numRSlice+1) * (numVSlice+1)) + 6 * (numRSlice);
	m_indexCount = m_vertexCount;
	
	ModelType** side = new ModelType*[numVSlice+1];
	if(!side)
	{
		return false;
	}
	ModelType* top = new ModelType[numRSlice + 1];
	if(!top)
	{
		return false;
	}
	ModelType* bottom = new ModelType[numRSlice + 1];
	if(!bottom)
	{
		return false;
	}

	int index = 0;
	float ang, hAct;
	float x, z;
	float u, v;
	int h1, a1;

	// Create temporary points for the side

	for (int h = 0; h <= numVSlice; h++)
	{
		side[h] = new ModelType[numRSlice+1];
		for (int a = 0; a <= numRSlice; a++)
		{
			ang = (float)a * 2 * D3DX_PI / numRSlice;
			hAct = h * Height / numVSlice;
			side[h][a].x = Radius * cos(ang);
			side[h][a].y = hAct;
			side[h][a].z = Radius * sin(ang);
			side[h][a].tu = ang / (2*D3DX_PI) * texScale;
			side[h][a].tv = (Height - hAct) / Height * texScale;
			side[h][a].nx = cos(ang);
			side[h][a].ny = 0;
			side[h][a].nz = sin(ang);
			side[h][a].bx = -sin(ang);
			side[h][a].by = 0;
			side[h][a].bz = cos(ang);
			side[h][a].tx = 0;
			side[h][a].ty = -1;
			side[h][a].tx = 0;
		}
	}
	
	// Create temporary points on the top and bottom caps

	for (int a = 0; a < numRSlice; a++)
	{
		ang = (float)a * 2 * D3DX_PI / numRSlice;
		x = Radius * cos(ang);
		z = Radius * sin(ang);
		u = (cos(ang) + 1) * .5f;
		v = (sin(ang) + 1) * .5f;
		
		top[index].x = x;
		top[index].y = Height;
		top[index].z = z;
		top[index].tu = u * texScale;
		top[index].tv = v * texScale;
		top[index].bx = 1.0f;
		top[index].by = 0.0f;
		top[index].bz = 0.0f;
		top[index].tx = 0.0f;
		top[index].ty = 0.0f;
		top[index].tz = 1.0f;

		bottom[index].x = x;
		bottom[index].y = 0;
		bottom[index].z = z;
		bottom[index].tu = u * texScale;
		bottom[index++].tv = v * texScale;
		bottom[index].bx = 0.0f;
		bottom[index].by = 0.0f;
		bottom[index].bz = 1.0f;
		bottom[index].tx = 1.0f;
		bottom[index].ty = 0.0f;
		bottom[index].tz = 0.0f;
	}

	top[index].x = 0;
	top[index].y = Height;
	top[index].z = 0;

	top[index].tu = .5f * texScale;
	top[index].tv = .5f * texScale;

	bottom[index].x = 0;
	bottom[index].y = 0;
	bottom[index].z = 0;

	bottom[index].tu = .5f * texScale;
	bottom[index].tv = .5f * texScale;



	// Fill in actual vertices

	m_model = new ModelType[m_vertexCount];
	if(!m_model)
	{
		return false;
	}

	index = 0;

	for (int h = 0; h < numVSlice; h++)
	{
		for (int a = 0; a < numRSlice; a++)
		{
			h1 = h+1;
			a1 = a+1;
			// first triangle
			m_model[index].x = side[h][a].x;
			m_model[index].y = side[h][a].y - Height * .5f;
			m_model[index].z = side[h][a].z;
			m_model[index].tu = side[h][a].tu;
			m_model[index].tv = side[h][a].tv;
			m_model[index].nx = side[h][a].nx;
			m_model[index].ny = side[h][a].ny;
			m_model[index].nz = side[h][a].nz;
			m_model[index].tx = side[h][a].tx;
			m_model[index].ty = side[h][a].ty;
			m_model[index].tz = side[h][a].tz;
			m_model[index].bx = side[h][a].by;
			m_model[index].by = side[h][a].by;
			m_model[index++].bz = side[h][a].bz;

			m_model[index].x = side[h1][a1].x;
			m_model[index].y = side[h1][a1].y - Height * .5f;
			m_model[index].z = side[h1][a1].z;
			m_model[index].tu = side[h1][a1].tu;
			m_model[index].tv = side[h1][a1].tv;
			m_model[index].nx = side[h1][a1].nx;
			m_model[index].ny = side[h1][a1].ny;
			m_model[index].nz = side[h1][a1].nz;
			m_model[index].tx = side[h1][a1].tx;
			m_model[index].ty = side[h1][a1].ty;
			m_model[index].tz = side[h1][a1].tz;
			m_model[index].bx = side[h1][a1].by;
			m_model[index].by = side[h1][a1].by;
			m_model[index++].bz = side[h1][a1].bz;

			m_model[index].x = side[h][a1].x;
			m_model[index].y = side[h][a1].y - Height * .5f;
			m_model[index].z = side[h][a1].z;
			m_model[index].tu = side[h][a1].tu;
			m_model[index].tv = side[h][a1].tv;
			m_model[index].nx = side[h][a1].nx;
			m_model[index].ny = side[h][a1].ny;
			m_model[index].nz = side[h][a1].nz;
			m_model[index].tx = side[h][a1].tx;
			m_model[index].ty = side[h][a1].ty;
			m_model[index].tz = side[h][a1].tz;
			m_model[index].bx = side[h][a1].by;
			m_model[index].by = side[h][a1].by;
			m_model[index++].bz = side[h][a1].bz;

			// second triangle
			m_model[index].x = side[h][a].x;
			m_model[index].y = side[h][a].y - Height * .5f;
			m_model[index].z = side[h][a].z;
			m_model[index].tu = side[h][a].tu;
			m_model[index].tv = side[h][a].tv;
			m_model[index].nx = side[h][a].nx;
			m_model[index].ny = side[h][a].ny;
			m_model[index].nz = side[h][a].nz;
			m_model[index].tx = side[h][a].tx;
			m_model[index].ty = side[h][a].ty;
			m_model[index].tz = side[h][a].tz;
			m_model[index].bx = side[h][a].by;
			m_model[index].by = side[h][a].by;
			m_model[index++].bz = side[h][a].bz;

			m_model[index].x = side[h1][a].x;
			m_model[index].y = side[h1][a].y - Height * .5f;
			m_model[index].z = side[h1][a].z;
			m_model[index].tu = side[h1][a].tu;
			m_model[index].tv = side[h1][a].tv;
			m_model[index].nx = side[h1][a].nx;
			m_model[index].ny = side[h1][a].ny;
			m_model[index].nz = side[h1][a].nz;
			m_model[index].tx = side[h1][a].tx;
			m_model[index].ty = side[h1][a].ty;
			m_model[index].tz = side[h1][a].tz;
			m_model[index].bx = side[h1][a].by;
			m_model[index].by = side[h1][a].by;
			m_model[index++].bz = side[h1][a].bz;

			m_model[index].x = side[h1][a1].x;
			m_model[index].y = side[h1][a1].y - Height * .5f;
			m_model[index].z = side[h1][a1].z;
			m_model[index].tu = side[h1][a1].tu;
			m_model[index].tv = side[h1][a1].tv;
			m_model[index].nx = side[h1][a1].nx;
			m_model[index].ny = side[h1][a1].ny;
			m_model[index].nz = side[h1][a1].nz;
			m_model[index].tx = side[h1][a1].tx;
			m_model[index].ty = side[h1][a1].ty;
			m_model[index].tz = side[h1][a1].tz;
			m_model[index].bx = side[h1][a1].by;
			m_model[index].by = side[h1][a1].by;
			m_model[index++].bz = side[h1][a1].bz;
		}
	}

	// fill the top and bottom caps

	for(int i=0; i<numRSlice; i++)
	{
		// one from the top	
		m_model[index].x = top[i].x;
		m_model[index].y = top[i].y - Height * .5f;
		m_model[index].z = top[i].z;
		m_model[index].tu = top[i].tu;
		m_model[index].tv = top[i].tv;
		m_model[index].nx = 0.0f;
		m_model[index].ny = 1.0f;
		m_model[index].nz = 0.0f;
		m_model[index].tx = 0.0f;
		m_model[index].ty = 0.0f;
		m_model[index].tz = 1.0f;
		m_model[index].bx = 1.0f;
		m_model[index].by = 0.0f;
		m_model[index++].bz = 0.0f;

		m_model[index].x = top[numRSlice].x;
		m_model[index].y = top[numRSlice].y - Height * .5f;
		m_model[index].z = top[numRSlice].z;
		m_model[index].tu = top[numRSlice].tu;
		m_model[index].tv = top[numRSlice].tv;
		m_model[index].nx = 0.0f;
		m_model[index].ny = 1.0f;
		m_model[index].nz = 0.0f;
		m_model[index].tx = 0.0f;
		m_model[index].ty = 0.0f;
		m_model[index].tz = 1.0f;
		m_model[index].bx = 1.0f;
		m_model[index].by = 0.0f;
		m_model[index++].bz = 0.0f;

		m_model[index].x = top[(i + 1)%numRSlice].x;
		m_model[index].y = top[(i + 1)%numRSlice].y - Height * .5f;
		m_model[index].z = top[(i + 1)%numRSlice].z;
		m_model[index].tu = top[(i + 1)%numRSlice].tu;
		m_model[index].tv = top[(i + 1)%numRSlice].tv;
		m_model[index].nx = 0.0f;
		m_model[index].ny = 1.0f;
		m_model[index].nz = 0.0f;
		m_model[index].tx = 0.0f;
		m_model[index].ty = 0.0f;
		m_model[index].tz = 1.0f;
		m_model[index].bx = 1.0f;
		m_model[index].by = 0.0f;
		m_model[index++].bz = 0.0f;
		
		//one from the bottom
		m_model[index].x = bottom[i].x;
		m_model[index].y = bottom[i].y - Height * .5f;
		m_model[index].z = bottom[i].z;
		m_model[index].tu = bottom[i].tu;
		m_model[index].tv = bottom[i].tv;
		m_model[index].nx = 0.0f;
		m_model[index].ny = -1.0f;
		m_model[index++].nz = 0.0f;

		
		m_model[index].x = bottom[(i + 1)%numRSlice].x;
		m_model[index].y = bottom[(i + 1)%numRSlice].y - Height * .5f;
		m_model[index].z = bottom[(i + 1)%numRSlice].z;
		m_model[index].tu = bottom[(i + 1)%numRSlice].tu;
		m_model[index].tv = bottom[(i + 1)%numRSlice].tv;
		m_model[index].nx = 0.0f;
		m_model[index].ny = -1.0f;
		m_model[index++].nz = 0.0f;

		m_model[index].x = bottom[numRSlice].x;
		m_model[index].y = bottom[numRSlice].y - Height * .5f;
		m_model[index].z = bottom[numRSlice].z;
		m_model[index].tu = bottom[numRSlice].tu;
		m_model[index].tv = bottom[numRSlice].tv;		
		m_model[index].nx = 0.0f;
		m_model[index].ny = -1.0f;
		m_model[index++].nz = 0.0f;
	}


	//if(!CalculateBNT())
	//{
	//	return false;
	//}

	// Clean up
	for(int i=0; i<numVSlice; i++)
	{
		delete [] side[i];
		side[i] = 0;
	}
	delete [] side;
	side = 0;

	delete[] top;
	top = 0;

	delete[] bottom;
	bottom = 0;

	return true;
}