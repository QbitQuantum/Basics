EStatusCode PreprocessorTest::RunTest(const string& inName, const string& inOriginalFile, const string& inOutputFile, const string& inComparisonFile)
{
	EStatusCode status = eSuccess;

	StringToStringMap preprocessorDefinitions;
	StringList includeFolders;

	includeFolders.push_back(scSamplesBasePath);
	preprocessorDefinitions.insert(StringToStringMap::value_type("PREDEFINED_SYMBOL","2"));

	InputFile sourceFile;
	sourceFile.OpenFile(inOriginalFile);

	OutputFile outputFile;
	outputFile.OpenFile(inOutputFile);
	mCurrentStream = outputFile.GetOutputStream();

	PreProcessor preProcessor;

	preProcessor.Setup(sourceFile.GetInputStream(),inOriginalFile,preprocessorDefinitions,includeFolders);

	preProcessor.AddListener(this);

	mStartRow = true;
	BoolAndString tokenizerResult = preProcessor.GetNextToken();
	while(tokenizerResult.first)
	{
		if(!mStartRow)
			mCurrentStream->Write((const Byte*)"  ",2); // 2 spaces, so we can clearly distinct tokens
		mCurrentStream->Write((const Byte*)tokenizerResult.second.c_str(),tokenizerResult.second.size());

		mStartRow = false;

		tokenizerResult = preProcessor.GetNextToken();
	}

	sourceFile.CloseFile();
	outputFile.CloseFile();

	mCurrentStream = NULL;
	
	SimpleFileComparer comparer;

	if(!comparer.Same(inOutputFile,inComparisonFile))
	{
		cout<<"TokenizerTest::Run, failed in test named "<<inName<<". see result in "<<inOutputFile<<" and compare with the required result in "<<inComparisonFile<<"\n";
		status = eFailure;
	}

	return status;	

}