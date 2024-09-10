bool CoinVisualizationNode::saveModel(const std::string &modelPath, const std::string &filename)
{
	std::string outFile = filename;

	boost::filesystem::path completePath(modelPath);
	boost::filesystem::path fn(outFile);

	if (!boost::filesystem::is_directory(completePath))
	{
		if (!boost::filesystem::create_directories(completePath))
		{
			VR_ERROR << "Could not create model dir  " << completePath.string() << endl;
			return false;
		}
	}

	boost::filesystem::path completeFile = boost::filesystem::operator/(completePath,fn);

    SoOutput* so = new SoOutput();
    if (!so->openFile(completeFile.string().c_str()))
    {
        VR_ERROR << "Could not open file " << completeFile.string() << " for writing." << endl;
    }
	SoGroup *n = new SoGroup;
	n->ref();
	n->addChild(visualization);
	SoGroup* newVisu = CoinVisualizationFactory::convertSoFileChildren(n);
	newVisu->ref();
    SoWriteAction wa(so);
    wa.apply(newVisu);
	so->closeFile();

	newVisu->unref();
	n->unref();

    return true;
}