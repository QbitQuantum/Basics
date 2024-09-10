void CFeatureHandler::LoadFeaturesFromMap(CFileHandler* file,bool onlyCreateDefs)
{
	file->Seek(readmap->header.featurePtr);
	MapFeatureHeader fh;
	READ_MAPFEATUREHEADER(fh, file);
	if(file->Eof()){
		info->AddLine("No features in map file?");
		return;
	}
	string* mapids=new string[fh.numFeatureType];

	for(int a=0;a<fh.numFeatureType;++a){
		char c;
		file->Read(&c,1);
		while(c){
			mapids[a]+=c;
			file->Read(&c,1);
		}
		string name=mapids[a];
		if(name.find("TreeType")!=string::npos){
			FeatureDef* fd=new FeatureDef;
			fd->blocking=1;
			fd->burnable=true;
			fd->destructable=1;
			fd->drawType=DRAWTYPE_TREE;
			fd->modelType=atoi(name.substr(8).c_str());
			fd->energy=250;
			fd->metal=0;
			fd->maxHealth=5;
			fd->radius=20;
			fd->xsize=2;
			fd->ysize=2;
			fd->myName=name;
			fd->mass=20;
			featureDefs[name]=fd;
		} else if(name.find("GeoVent")!=string::npos){
			FeatureDef* fd=new FeatureDef;
			fd->blocking=0;
			fd->burnable=0;
			fd->destructable=0;
			fd->geoThermal=1;
			fd->drawType=DRAWTYPE_NONE;	//geos are drawn into the ground texture and emit smoke to be visible
			fd->modelType=0;
			fd->energy=0;
			fd->metal=0;
			fd->maxHealth=0;
			fd->radius=0;
			fd->xsize=0;
			fd->ysize=0;
			fd->myName=name;
			fd->mass=100000;
			featureDefs[name]=fd;
		} else if(wreckParser.SectionExist(name)){
			GetFeatureDef(name);
		} else {
			info->AddLine("Unknown feature type %s",name.c_str());
		}
	}

	if(!onlyCreateDefs){
		for(int a=0;a<fh.numFeatures;++a){
			MapFeatureStruct ffs;
			READ_MAPFEATURESTRUCT(ffs, file);

			string name=mapids[ffs.featureType];

			ffs.ypos=ground->GetHeight2(ffs.xpos,ffs.zpos);
			CFeature *f = new CFeature;
			f->Initialize (float3(ffs.xpos,ffs.ypos,ffs.zpos),featureDefs[name],(short int)ffs.rotation,-1,"");
		}
	}

	delete[] mapids;
}