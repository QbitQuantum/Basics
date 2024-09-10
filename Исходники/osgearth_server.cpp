    void handleRequest(HTTPServerRequest& request,
                       HTTPServerResponse& response)
    {
        StringTokenizer tok("/");
        StringVector tized;
        tok.tokenize(request.getURI(), tized);            
        if ( tized.size() == 4 )
        {
            int z = as<int>(tized[1], 0);
            int x = as<int>(tized[2], 0);
            unsigned int y = as<int>(osgDB::getNameLessExtension(tized[3]),0);
            std::string ext = osgDB::getFileExtension(tized[3]);

            OE_DEBUG << "z=" << z << std::endl;
            OE_DEBUG << "x=" << x << std::endl;
            OE_DEBUG << "y=" << y << std::endl;              
            OE_DEBUG << "ext=" << ext << std::endl;

            response.setChunkedTransferEncoding(true);

            osg::ref_ptr< osg::Image > image = _server->getTile(z, x, y);
            
            if (image)
            {
                osgDB::ReaderWriter* rw = osgDB::Registry::instance()->getReaderWriterForExtension(ext);
                if (rw)
                {
                    std::string mime = "image/png";
                    if (ext == "jpeg" || ext == "jpg")
                    {
                        mime = "image/jpeg";
                    }                    
                    response.setContentType(mime);
                    std::ostream& ostr = response.send();                 
                    rw->writeImage(*image.get(), ostr);                    
                }             

            }
        }
 
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);                
    }