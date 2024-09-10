bool SolverCalculateNormals::LoadShaders()
{
	if (true == mNeedProgramReload)
	{
		mProgramZero.Clear();
		mProgramNorm.Clear();
		mProgramRecomputeNormals.Clear();
		mNeedProgramReload = false;
	}

	// check for a compute shader
	/*
	if (false == mProgramZero.PrepProgram("\\GLSL_CS\\recomputeNormalsZero.cs") )
		return false;

	if (false == mProgramRecomputeNormals.PrepProgram("\\GLSL_CS\\recomputeNormals.cs") )
		return false;
	
	if (false == mProgramNorm.PrepProgram("\\GLSL_CS\\recomputeNormalsNorm.cs") )
		return false;
		*/

	
	if (0 == mProgramZero.GetProgramId() )
	{
		bool res = false;
		char* data = nullptr;
		HINSTANCE hInst = GetThisModuleHandle();
		
		HRSRC hRes = FindResourceEx(hInst,
                           "TEXT",
                           MAKEINTRESOURCE(IDR_TEXT1),
                           MAKELANGID(LANG_NEUTRAL,
                           SUBLANG_NEUTRAL));
						   
		if(nullptr != hRes)
		{
			HGLOBAL hData = LoadResource(hInst, hRes);
			if (hData)
			{
				DWORD dataSize = SizeofResource(hInst, hRes);
				data = (char*)LockResource(hData);
				
				char *shaderData = new char[dataSize+1];
				memset( shaderData, 0, sizeof(char) * (dataSize+1) );
				memcpy( shaderData, data, sizeof(char) * dataSize );

				res = mProgramZero.PrepProgramFromBuffer(shaderData, "recomputeNormalsZero");
				
				delete [] shaderData;

				UnlockResource(hData);
			}
		}

		if (false == res)
		{
			Active =false;
			return false;
		}
	}
	if (0 == mProgramNorm.GetProgramId() )
	{
		bool res = false;
		char* data = nullptr;
		HINSTANCE hInst = GetThisModuleHandle();
		
		HRSRC hRes = FindResourceEx(hInst,
                           "TEXT",
                           MAKEINTRESOURCE(IDR_TEXT2),
                           MAKELANGID(LANG_NEUTRAL,
                           SUBLANG_NEUTRAL));
		if(nullptr != hRes)
		{
			HGLOBAL hData = LoadResource(hInst, hRes);
			if (hData)
			{
				DWORD dataSize = SizeofResource(hInst, hRes);
				data = (char*)LockResource(hData);

				char *shaderData = new char[dataSize+1];
				memset( shaderData, 0, sizeof(char) * (dataSize+1) );
				memcpy( shaderData, data, sizeof(char) * dataSize );

				res = mProgramNorm.PrepProgramFromBuffer(shaderData, "recomputeNormalsNorm");
				
				delete [] shaderData;

				UnlockResource(hData);
			}
		}

		if (false == res)
		{
			Active =false;
			return false;
		}
	}
	if (0 == mProgramRecomputeNormals.GetProgramId() )
	{
		bool res = false;
		char* data = nullptr;
		HINSTANCE hInst = GetThisModuleHandle();
		
		HRSRC hRes = FindResourceEx(hInst,
                           "TEXT",
                           MAKEINTRESOURCE(IDR_TEXT3),
                           MAKELANGID(LANG_NEUTRAL,
                           SUBLANG_NEUTRAL));
		if(nullptr != hRes)
		{
			HGLOBAL hData = LoadResource(hInst, hRes);
			if (hData)
			{
				DWORD dataSize = SizeofResource(hInst, hRes);
				data = (char*)LockResource(hData);

				char *shaderData = new char[dataSize+1];
				memset( shaderData, 0, sizeof(char) * (dataSize+1) );
				memcpy( shaderData, data, sizeof(char) * dataSize );

				res = mProgramRecomputeNormals.PrepProgramFromBuffer(shaderData, "recomputeNormals");
				
				delete [] shaderData;

				UnlockResource(hData);
			}
		}

		if (false == res)
		{
			Active =false;
			return false;
		}
	}

	return true;
}