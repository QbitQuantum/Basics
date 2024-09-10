void CFaceModel::LoadObjFilename(const std::string &filename, bool landmarks)
{
	AABBMin = float3(10000.0f, 10000.0f, 10000.0f);
	AABBMax = -AABBMin;

	mObjFilename = filename;
	{
		tObjModel objModel;
		objLoader(filename.c_str(), objModel);
		CopyOBJDataToSoftwareMesh(&objModel, &mMesh);
	}

	float boxSize = 8.0f;
	int vertCount = mMesh.GetVertCount();
	if (vertCount > 0)
	{
		float3 vmin = mMesh.Pos[0];
		float3 vmax = mMesh.Pos[0];

		for (int i = 0; i < vertCount; i++)
		{
			vmin = Min(vmin, mMesh.Pos[i]);
			vmax = Max(vmax, mMesh.Pos[i]);
		}

		float3 center = (vmax + vmin) / 2.0f;
		float3 dim = vmax - vmin;

		float maxDim = floatMax(dim.x, floatMax(dim.y, dim.z));

		mVertOffset = -center;
		mVertScale = boxSize / maxDim;

		// center to origin, scale, and rotate
		// 
		for (int i = 0; i < vertCount; i++)
		{
			float3 *pos = &mMesh.Pos[i];
			*pos -= center;
			*pos *= mVertScale;
			Swap(pos->z, pos->y);

			// save scale and rotate from RSSDK format. Z is up in rssdk
			mMesh.Tex[i].y = 1.0f - mMesh.Tex[i].y;

			AABBMin = Min(*pos, AABBMin);
			AABBMax = Max(*pos, AABBMax);
		}
	}
	LoadLandmarks();

	// load texture
	SAFE_RELEASE(mTexture);
	std::string fnString = mObjFilename;
	int lastindex = (int)fnString.find_last_of(".");
	std::string rawname = fnString.substr(0, lastindex);
	std::string textureName = rawname.append("image1.png");
	mTexture = CPUTTexture::Create(std::string("facetexture"), textureName, false);

	FlagUpdated();
}