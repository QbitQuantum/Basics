EStatusCode PFBStreamTest::Run(const TestConfiguration& inTestConfiguration)
{
	EStatusCode status;
	InputFile pfbFile;
	OutputFile decodedPFBFile;
	InputPFBDecodeStream decodeStream;

	do
	{
		pfbFile.OpenFile(RelativeURLToLocalPath(inTestConfiguration.mSampleFileBase,"TestMaterials/fonts/HLB_____.PFB"));

		decodedPFBFile.OpenFile(RelativeURLToLocalPath(inTestConfiguration.mSampleFileBase,"decodedPFBFile.txt"));


		status = decodeStream.Assign(pfbFile.GetInputStream());
		
		if(status != PDFHummus::eSuccess)
		{
			cout<<"Failed to assign pfb input stream";
			break;
		}

		OutputStreamTraits traits(decodedPFBFile.GetOutputStream());

		status = traits.CopyToOutputStream(&decodeStream);

		if(status != PDFHummus::eSuccess)
		{
			cout<<"Failed to decode pfb stream";
			break;
		}
	}while(false);

	decodeStream.Assign(NULL);
	pfbFile.CloseFile();
	decodedPFBFile.CloseFile();

	return status;
}