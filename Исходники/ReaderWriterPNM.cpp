        virtual WriteResult writeImage(const osg::Image& image,const std::string& fileName, const osgDB::ReaderWriter::Options* options) const
        {
            // Only ppm format output supported
            std::string ext = osgDB::getFileExtension(fileName);
            if ( !osgDB::equalCaseInsensitive(ext, "ppm") ) return WriteResult::FILE_NOT_HANDLED;
            
            // only support rgb images right now.
            if (image.getPixelFormat()!=GL_RGB || image.getDataType()!=GL_UNSIGNED_BYTE) return WriteResult("Error image pixel format not supported by pnm writer.");

            osgDB::ofstream fout(fileName.c_str(), std::ios::out | std::ios::binary);
            if(!fout) return WriteResult::ERROR_IN_WRITING_FILE;

            return writeImage(image,fout,options);
        }