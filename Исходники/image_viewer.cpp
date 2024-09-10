ReplayCreateStatus IMG_CreateReplayDevice(const char *logfile, IReplayDriver **driver)
{
	FILE *f = FileIO::fopen(logfile, "rb");

	if(!f)
		return eReplayCreate_FileIOFailed;
		
	FetchTexture texDetails;

	ResourceFormat rgba8_unorm;
	rgba8_unorm.compByteWidth = 1;
	rgba8_unorm.compCount = 4;
	rgba8_unorm.compType = eCompType_UNorm;
	rgba8_unorm.special = false;

	ResourceFormat rgba32_float = rgba8_unorm;
	rgba32_float.compByteWidth = 4;
	rgba32_float.compType = eCompType_Float;

	texDetails.creationFlags = eTextureCreate_SwapBuffer|eTextureCreate_RTV;
	texDetails.cubemap = false;
	texDetails.customName = true;
	texDetails.name = logfile;
	texDetails.ID = ResourceId();
	texDetails.byteSize = 0;
	texDetails.msQual = 0;
	texDetails.msSamp = 1;

	// reasonable defaults for everything but dds
	texDetails.numSubresources = 1;
	texDetails.dimension = 2;
	texDetails.arraysize = 1;
	texDetails.depth = 1;
	texDetails.mips = 1;

	byte *data = NULL;
	size_t datasize = 0;

	bool dds = false;

	if(is_exr_file(f))
	{
		texDetails.format = rgba32_float;
		
		FileIO::fseek64(f, 0, SEEK_SET);

		const char *err = NULL;

		int ret = LoadEXRFP((float **)&data, (int *)&texDetails.width, (int *)&texDetails.height, f, &err);
		datasize = texDetails.width*texDetails.height*4*sizeof(float);

		// could be an unsupported form of EXR, like deep image or other
		if(ret != 0)
		{
			if(data) free(data);
			RDCERR("EXR file detected, but couldn't load with LoadEXR %d: '%s'", ret, err);
			return eReplayCreate_APIUnsupported;
		}
	}
	else if(stbi_is_hdr_from_file(f))
	{
		texDetails.format = rgba32_float;

		FileIO::fseek64(f, 0, SEEK_SET);

		int ignore = 0;
		data = (byte *)stbi_loadf_from_file(f, (int *)&texDetails.width, (int *)&texDetails.height, &ignore, 4);
		datasize = texDetails.width*texDetails.height*4*sizeof(float);
	}
	else if(is_dds_file(f))
	{
		dds = true;
	}
	else
	{
		int ignore = 0;
		int ret = stbi_info_from_file(f, (int *)&texDetails.width, (int *)&texDetails.height, &ignore);

		// just in case (we shouldn't have come in here if this weren't true), make sure
		// the format is supported
		if(ret == 0 ||
			 texDetails.width == 0 || texDetails.width == ~0U ||
			 texDetails.height == 0 || texDetails.height == ~0U)
		{
			return eReplayCreate_APIUnsupported;
		}

		texDetails.format = rgba8_unorm;

		data = stbi_load_from_file(f, (int *)&texDetails.width, (int *)&texDetails.height, &ignore, 4);
		datasize = texDetails.width*texDetails.height*4*sizeof(byte);
	}
	
	// if we don't have data at this point (and we're not a dds file) then the
	// file was corrupted and we failed to load it
	if(!dds && data == NULL)
	{
		return eReplayCreate_FileCorrupted;
	}
	
	IReplayDriver *proxy = NULL;
	auto status = RenderDoc::Inst().CreateReplayDriver(RDC_Unknown, NULL, &proxy);
	
	if(status != eReplayCreate_Success || !proxy)
	{
		if(proxy) proxy->Shutdown();
		return status;
	}

	ResourceId id;

	if(!dds)
	{
		id = proxy->CreateProxyTexture(texDetails);

		proxy->SetProxyTextureData(id, 0, 0, data, datasize);
		free(data);
	}
	else
	{
		FileIO::fseek64(f, 0, SEEK_SET);
		dds_data read_data = load_dds_from_file(f);
		
		if(read_data.subdata == NULL)
		{
			proxy->Shutdown();
			return eReplayCreate_FileCorrupted;
		}

		texDetails.cubemap = read_data.cubemap;
		texDetails.arraysize = read_data.slices;
		texDetails.width = read_data.width;
		texDetails.height = read_data.height;
		texDetails.depth = read_data.depth;
		texDetails.mips = read_data.mips;
		texDetails.numSubresources = texDetails.arraysize*texDetails.mips;
		texDetails.format = read_data.format;
		                         texDetails.dimension = 1;
		if(texDetails.width > 1) texDetails.dimension = 2;
		if(texDetails.depth > 1) texDetails.dimension = 3;

		id = proxy->CreateProxyTexture(texDetails);

		for(uint32_t i=0; i < texDetails.numSubresources; i++)
		{
			proxy->SetProxyTextureData(id, i/texDetails.mips, i%texDetails.mips, read_data.subdata[i], (size_t)read_data.subsizes[i]);

			delete[] read_data.subdata[i];
		}

		delete[] read_data.subdata;
		delete[] read_data.subsizes;
	}

	*driver = new ImageViewer(proxy, logfile, id);

	FileIO::fclose(f);

	return eReplayCreate_Success;
}