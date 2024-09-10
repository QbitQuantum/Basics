void GRecommenderLib::fillMissingValues(GArgReader& args)
{
	unsigned int seed = getpid() * (unsigned int)time(NULL);
	bool normalize = true;
	while(args.next_is_flag())
	{
		if(args.if_pop("-seed"))
			seed = args.pop_uint();
		else if(args.if_pop("-nonormalize"))
			normalize = false;
		else
			throw Ex("Invalid option: ", args.peek());
	}

	// Load the data and the filter
	GMatrix dataOrig;
	dataOrig.loadArff(args.pop_string());

	// Parse params
	vector<size_t> ignore;
	while(args.next_is_flag())
	{
		if(args.if_pop("-ignore"))
			parseAttributeList(ignore, args, dataOrig.cols());
		else
			throw Ex("Invalid option: ", args.peek());
	}

	// Throw out the ignored attributes
	std::sort(ignore.begin(), ignore.end());
	for(size_t i = ignore.size() - 1; i < ignore.size(); i--)
		dataOrig.deleteColumns(ignore[i], 1);

	GRelation* pOrigRel = dataOrig.relation().clone();
	std::unique_ptr<GRelation> hOrigRel(pOrigRel);
	GCollaborativeFilter* pModel = InstantiateAlgorithm(args);
	std::unique_ptr<GCollaborativeFilter> hModel(pModel);
	if(args.size() > 0)
		throw Ex("Superfluous argument: ", args.peek());
	pModel->rand().setSeed(seed);

	// Convert to all normalized real values
	GNominalToCat* pNtc = new GNominalToCat();
	GIncrementalTransform* pFilter = pNtc;
	std::unique_ptr<GIncrementalTransformChainer> hChainer;
	if(normalize)
	{
		GIncrementalTransformChainer* pChainer = new GIncrementalTransformChainer(new GNormalize(), pNtc);
		hChainer.reset(pChainer);
		pFilter = pChainer;
	}
	pNtc->preserveUnknowns();
	pFilter->train(dataOrig);
	GMatrix* pData = pFilter->transformBatch(dataOrig);
	std::unique_ptr<GMatrix> hData(pData);

	// Convert to 3-column form
	GMatrix* pMatrix = new GMatrix(0, 3);
	std::unique_ptr<GMatrix> hMatrix(pMatrix);
	size_t dims = pData->cols();
	for(size_t i = 0; i < pData->rows(); i++)
	{
		GVec& row = pData->row(i);
		for(size_t j = 0; j < dims; j++)
		{
			if(row[j] != UNKNOWN_REAL_VALUE)
			{
				GVec& vec = pMatrix->newRow();
				vec[0] = (double)i;
				vec[1] = (double)j;
				vec[2] = row[j];
			}
		}
	}

	// Train the collaborative filter
	pModel->train(*pMatrix);
	hMatrix.release();
	pMatrix = NULL;

	// Predict values for missing elements
	for(size_t i = 0; i < pData->rows(); i++)
	{
		GVec& row = pData->row(i);
		for(size_t j = 0; j < dims; j++)
		{
			if(row[j] == UNKNOWN_REAL_VALUE)
				row[j] = pModel->predict(i, j);
			GAssert(row[j] != UNKNOWN_REAL_VALUE);
		}
	}

	// Convert the data back to its original form
	GMatrix* pOut = pFilter->untransformBatch(*pData);
	pOut->setRelation(hOrigRel.release());
	pOut->print(cout);
}