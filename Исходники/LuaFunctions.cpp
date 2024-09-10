	CObject_pointer<CFeature>* FeatureLoaderLoadFeature( string name, float3 pos, int team )
	{
		FeatureDef *def = featureHandler->GetFeatureDef(name);
		CFeature* feature = new CFeature();
		feature->Initialize( pos,def,0, 0, team,"" );
		return new CObject_pointer<CFeature>(feature);
	}