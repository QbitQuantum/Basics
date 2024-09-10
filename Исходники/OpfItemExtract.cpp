amis::AmisError amis::OpfItemExtract::openFile(string filepath)
{
    //local variables
    const char* cp_file;
    string tmp_string;
    XmlReader parser;

    mb_flagFinished = false;
    mHref = "";

    mFilepath = amis::FilePathTools::getAsLocalFilePath(filepath);
    mFilepath = amis::FilePathTools::clearTarget(filepath);

    mError.setCode(amis::OK);
    mError.setMessage("");
    mError.setFilename(filepath);

    //do a SAX parse of this new file
    cp_file = mFilepath.c_str();

    parser.setContentHandler(this);
    parser.setErrorHandler(this);

    if (!parser.parseXml(cp_file))
    {
        const XmlError *e = parser.getLastError();
        if (e)
        {
            LOG4CXX_ERROR(amisOpfItemExtractLog,
                    "Error in OpfItemExtract: " << e->getMessage());
            mError.loadXmlError(*e);
        }
        else
        {
            LOG4CXX_ERROR(amisOpfItemExtractLog,
                    "Unknown error in OpfItemExtract");
            mError.setCode(UNDEFINED_ERROR);
        }
    }

    return mError;
}