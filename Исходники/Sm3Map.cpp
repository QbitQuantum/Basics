void CSm3ReadMap::Initialize (const char *mapname)
{
	try {
		string lmsg = "Loading " + string(mapname);
		PrintLoadMsg(lmsg.c_str());
		GLint tu;
		glGetIntegerv(GL_MAX_TEXTURE_UNITS, &tu);

		renderer = SAFE_NEW terrain::Terrain;

		renderer->config.cacheTextures=false;

		renderer->config.forceFallbackTexturing = !!configHandler.GetInt("SM3ForceFallbackTex", 0);

		if (!renderer->config.forceFallbackTexturing && GLEW_ARB_fragment_shader && GLEW_ARB_shading_language_100) {
			renderer->config.useBumpMaps = true;
			renderer->config.anisotropicFiltering = 0.0f;
		}

		renderer->config.useStaticShadow = false;

		renderer->config.terrainNormalMaps = false;
		renderer->config.normalMapLevel = 3;

		if (shadowHandler->drawShadows)
			renderer->config.useShadowMaps = true;

		if (!mapInfo->sm3.minimap.empty()) {
			CBitmap bmp;
			if(bmp.Load(mapInfo->sm3.minimap))
				minimapTexture=bmp.CreateTexture(true);
		}

/*		int numStages=atoi(mapDefParser.SGetValueDef("0", "map\\terrain\\numtexturestages").c_str());
		int maxStages=configHandler.GetInt("SM3MaxTextureStages", 10);
		if (numStages > maxStages) {
			renderer->config.cacheTextures = true;
			renderer->config.cacheTextureSize = 256;
		//	renderer->config.detailMod
		}
*/
		Sm3LoadCB loadcb;
		terrain::LightingInfo lightInfo;
		lightInfo.ambient = mapInfo->light.groundAmbientColor;
		terrain::StaticLight light;
		light.color = mapInfo->light.groundSunColor;
		light.directional = false;
		light.position = mapInfo->light.sunDir *1000000;
		lightInfo.staticLights.push_back (light);
		renderer->Load (GetMapDefParser(), &lightInfo, &loadcb);

		height = width = renderer->GetHeightmapWidth ()-1;

		// Set global map info
		gs->mapx=width;
		gs->mapy=height;
		gs->mapSquares = width*height;
		gs->hmapx=width/2;
		gs->hmapy=height/2;
		gs->pwr2mapx=next_power_of_2(width);
		gs->pwr2mapy=next_power_of_2(height);

		float3::maxxpos=width*SQUARE_SIZE-1;
		float3::maxzpos=height*SQUARE_SIZE-1;

		CReadMap::Initialize();

		const TdfParser& mapDefParser = GetMapDefParser();
		if (mapDefParser.SectionExist("map\\featuretypes")) {
			int numTypes = atoi(mapDefParser.SGetValueDef("0", "map\\featuretypes\\numtypes").c_str());
			for (int a=0;a<numTypes;a++) {
				char loc[100];
				SNPRINTF(loc, 100, "map\\featuretypes\\type%d", a);
				featureTypes.push_back (SAFE_NEW std::string(mapDefParser.SGetValueDef("TreeType0", loc)));
			}
		}
		LoadFeatureData();

		groundDrawer = SAFE_NEW CSm3GroundDrawer (this);
	}
	catch(content_error& e)
	{
		ErrorMessageBox(e.what(), "Error:", MBF_OK);
	}
}