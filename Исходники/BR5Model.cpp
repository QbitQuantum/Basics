	bool CBR5Model::loadFromFile(std::string fileName)
	{
		/* ***************** 1. load the data ***************** */

		FILE *br5 = fopen(fileName.c_str(),"rb");

		if (!br5)
		{
			return false;
		}

		long fileSize = getFileSize(br5);

		byte *data = new byte[fileSize];
		byte *tmp = data;

		// read the full model data
		size_t read = fread(data,sizeof(byte),fileSize,br5);

		if (read!=fileSize)
		{
			return false;
		}

		// read the mark
		char mark[3];
		memcpy(mark,data,3);
		data+=3;

		if (mark[0]!='B' || mark[1]!='R' || mark[2]!='5')
		{
			// file is not a valid br5 model
			fclose(br5);
			return false;
		}

		// read texture name
		memcpy(textureName,data,256);
		data+=256;

		// read number of vertices
		vertexCount = *(unsigned int*)data;
		data+=4;

		textureCoordinates = new float[vertexCount*2];

		// read texture coordinates
		memcpy(textureCoordinates,data,sizeof(float)*vertexCount*2);
		data+=sizeof(float)*vertexCount*2;

		// read number of frames
		framesCount = *(unsigned int*)data;
		data+=4;

		if (framesCount==1)
		{
			// non animated version

			// read vertices
			vertexCoordinates = new float[vertexCount*3];
			memcpy(vertexCoordinates,data,sizeof(float)*vertexCount*3);
			data+=sizeof(float)*vertexCount*3;
		}
		else
		{
			// read vertices
			/*vertexCoordinates = new float[vertexCount*3];
			memcpy(vertexCoordinates,data,sizeof(float)*vertexCount*3);
			data+=sizeof(float)*vertexCount*3;*/

			// read other anims
			vertexCoordinatesAnim = new float*[framesCount];

			for (unsigned int i=0; i<framesCount; i++)
			{
				vertexCoordinatesAnim[i] = new float[vertexCount*3];
				memcpy(vertexCoordinatesAnim[i],data,sizeof(float)*vertexCount*3);
				data+=sizeof(float)*vertexCount*3;
			}

			vertexCoordinates = new float[vertexCount*3];

			memcpy(vertexCoordinates,vertexCoordinatesAnim[0],sizeof(float)*vertexCount*3);
		}

		fclose(br5);

		data = tmp;
		delete [] data;

		startFrame = 0;
		endFrame = framesCount-1;


		/* ***************** 3. setup the VBO ***************** */

		vbo = new CVBO(framesCount==1?CVBO::BT_STATIC_DRAW:CVBO::BT_STREAM_DRAW,false);
		vbo->setVertexData(vertexCount,3,sizeof(GLfloat),vertexCoordinates,CVBO::DT_FLOAT);
		vbo->setEnumMode(CVBO::EM_TRIANGLES);

		setupTexture();

		// calculate the bounding box
		boundingBox.reset();
		for (unsigned int v=0; v<vertexCount*3; v+=3)
		{
			boundingBox.update(vertexCoordinates+v);
		}
		boundingBox.calculateExtents();

		return true;
	}