//-------------------------------------------------------------------------------------------------
// loads MD2 model
bool JMD2Model::Load(char *filename, char *textureName)
{

	//FILE *filePtr;						// file pointer
	int fileLen;						// length of model file
    char *buffer;						// file buffer
		
	modelHeader_t *modelHeader;			// model header

	stIndex_t *stPtr;					// texture data
    frame_t *frame;						// frame data
	Vector3D *pointListPtr;				// index variable
    mesh_t *triIndex, *bufIndexPtr;		// index variables
    int i, j;							// index variables

	// open the model file

	JFileSystem* fileSystem = JFileSystem::GetInstance();
	if (!fileSystem->OpenFile(filename))
		return false;
	//filePtr = fopen(filename, "rb");
	//if (filePtr == NULL)
	//	return false;

	// find length of file
    //fseek(filePtr, 0, SEEK_END);
    //fileLen = ftell(filePtr);
    //fseek(filePtr, 0, SEEK_SET);

	fileLen = fileSystem->GetFileSize();
	
    // read entire file into buffer
    buffer = (char*)malloc(fileLen + 1);
    //fread(buffer, sizeof(char), fileLen, filePtr);
	fileSystem->ReadFile(buffer, fileLen);
	fileSystem->CloseFile();

	// extract model file header from buffer
    modelHeader = (modelHeader_t*)buffer;

	// allocate memory for model data
   	mModel = (modelData_t*)malloc(sizeof(modelData_t));
	if (mModel == NULL)
		return false;

	// allocate memory for all vertices used in model, including animations
    mModel->pointList = (Vector3D *)malloc(sizeof(Vector3D)*modelHeader->numXYZ * modelHeader->numFrames);

	// store vital model data
    mModel->numPoints = modelHeader->numXYZ;
    mModel->numFrames = modelHeader->numFrames;
	mModel->frameSize = modelHeader->framesize;

    // loop number of frames in model file
    for(j = 0; j < modelHeader->numFrames; j++)
    {
       // offset to the points in this frame
       frame = (frame_t*)&buffer[modelHeader->offsetFrames + modelHeader->framesize * j];

	   // calculate the point positions based on frame details
       pointListPtr = (Vector3D *)&mModel->pointList[modelHeader->numXYZ * j];
       for(i = 0; i < modelHeader->numXYZ; i++)
       {
          pointListPtr[i].x = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
          pointListPtr[i].y = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
          pointListPtr[i].z = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
       }
    }
			 
	JTexture *tex = mRenderer->LoadTexture(textureName);
	if (tex)
		mModel->modelTex = tex;
	else
	{
		free(mModel);
		mModel = NULL;
		
		free(buffer);
		return false;
	}

	float texWidth = (float)tex->mWidth;
	float texHeight = (float)tex->mHeight;


    // allocate memory for the model texture coordinates
    mModel->st = (texCoord_t*)malloc(sizeof(texCoord_t)*modelHeader->numST);

	// store number of texture coordinates
    mModel->numST = modelHeader->numST;

	// set texture pointer to texture coordinate offset
    stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];

	// calculate and store the texture coordinates for the model
    for (i = 0; i < modelHeader->numST; i++)
    {
		mModel->st[i].s = (float)stPtr[i].s / texWidth;
        mModel->st[i].t = (float)stPtr[i].t / texHeight;
    }

	// allocate an index of triangles
	triIndex = (mesh_t*)malloc(sizeof(mesh_t) * modelHeader->numTris);

	// set total number of triangles
	mModel->numTriangles = modelHeader->numTris;
	mModel->triIndex = triIndex;
	
	// point to triangle indexes in buffer
	bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];

	// create a mesh (triangle) list
	for (j = 0; j < mModel->numFrames; j++)		
	{
		// for all triangles in each frame
		for(i = 0; i < modelHeader->numTris; i++)
		{
		   triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
		   triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
		   triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
		   triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
		   triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
		   triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
		}
	}

	// close file and free memory
	//fclose(filePtr);
    free(buffer);

	mModel->currentFrame = 0;
	mModel->nextFrame = 1;
	mModel->interpol = 0.0;

	CheckNextState();

    return true;
}