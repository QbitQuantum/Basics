EStatusCode PDFWriter::ModifyPDF(const std::string& inModifiedFile,
                                            EPDFVersion inPDFVersion,
                                            const std::string& inOptionalAlternativeOutputFile,
                                            const LogConfiguration& inLogConfiguration,
                                            const PDFCreationSettings& inPDFCreationSettings)
{
    EStatusCode status = eSuccess;
    
    SetupLog(inLogConfiguration);
	SetupObjectsContext(inPDFCreationSettings);
	
    do 
    {
        // either append to original file, or create a new copy and "modify" it. depending on users choice
        if(inOptionalAlternativeOutputFile.size() == 0 || (inOptionalAlternativeOutputFile == inModifiedFile))
        {
            status = mOutputFile.OpenFile(inModifiedFile,true);
            if(status != eSuccess)
                break;
        }
        else
        {
            status = mOutputFile.OpenFile(inOptionalAlternativeOutputFile);
            if(status != eSuccess)
               break;
            
            // copy original to new output file
            InputFile modifiedFileInput;
            status = modifiedFileInput.OpenFile(inModifiedFile);
            if(status != eSuccess)
                break;
            
            OutputStreamTraits traits(mOutputFile.GetOutputStream());
            status = traits.CopyToOutputStream(modifiedFileInput.GetInputStream());
            if(status != eSuccess)
                break;
        }
        
        mObjectsContext.SetOutputStream(mOutputFile.GetOutputStream());
        mDocumentContext.SetOutputFileInformation(&mOutputFile);
        
        // do setup for modification 
        mIsModified = true;
        status = SetupStateFromModifiedFile(inModifiedFile,inPDFVersion);
    } 
    while (false);
           
    return status;
}