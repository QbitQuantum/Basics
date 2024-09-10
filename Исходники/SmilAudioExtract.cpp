//--------------------------------------------------
amis::AmisError SmilAudioExtract::getAudioAtId(string filepath,
        amis::AudioNode** pAudioInfo)
{
    //local variables
    const char* cp_file;
    string tmp_string;
    XmlReader parser;

    mb_flagInPar = false;
    mb_flagFoundId = false;
    mb_flagFinished = false;

    mpAudioInfo = NULL;

    mError.setCode(amis::OK);
    mError.setMessage("");
    mError.setFilename(filepath);

    mId = amis::FilePathTools::getTarget(filepath);

    mFilePath = amis::FilePathTools::getAsLocalFilePath(filepath);
    mFilePath = amis::FilePathTools::clearTarget(filepath);

    //do a SAX parse of this new file
    cp_file = mFilePath.c_str();

    parser.setContentHandler(this);
    parser.setErrorHandler(this);

    if (!parser.parseXml(cp_file))
    {
        const XmlError *e = parser.getLastError();
        if (e)
        {
            LOG4CXX_ERROR(amisSmilAudioExtractLog,
                    "Error in SmilAudioExtract: " << e->getMessage());
            mError.loadXmlError(*e);
        }
        else
        {
            LOG4CXX_ERROR(amisSmilAudioExtractLog,
                    "Unknown error in SmilAudioExtract");
            mError.setCode(UNDEFINED_ERROR);
        }
    }

    if (mpAudioInfo != NULL)
        *pAudioInfo = mpAudioInfo;

    return mError;
}