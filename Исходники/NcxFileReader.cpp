amis::AmisError NcxFileReader::open(string filepath, NavModel* pModel)
{
    amis::AmisError err;

    LOG4CXX_DEBUG(amisNcxFileReadLog, "NcxFileReader opening: " << filepath);

    mOpenNodes.clear();
    mpCurrentNavPoint = NULL;

    mError.setCode(amis::OK);
    mError.setMessage("");
    mError.setFilename(filepath);

    XmlReader parser;

    mFilePath = amis::FilePathTools::getAsLocalFilePath(filepath);
    mpNavModel = pModel;

    //push the root onto the open nodes list
    mOpenNodes.push_back(mpNavModel->getNavMap()->getRoot());

    parser.setContentHandler(this);
    parser.setErrorHandler(this);

    if (!parser.parseXml(mFilePath.c_str()))
    {
        const XmlError *e = parser.getLastError();
        if (e)
        {
            LOG4CXX_ERROR(amisNcxFileReadLog,
                          "Error in NcxFileReader: " << e->getMessage());
            mError.loadXmlError(*e);
        }
        else
        {
            LOG4CXX_ERROR(amisNcxFileReadLog, "Unknown error in NcxFileReader");
            mError.setCode(amis::UNDEFINED_ERROR);
        }

    }

    return mError;

}