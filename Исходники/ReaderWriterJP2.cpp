        virtual WriteResult writeImage(const osg::Image &img,const std::string& fileName, const osgDB::ReaderWriter::Options* options) const
        {
            std::string ext = osgDB::getFileExtension(fileName);
            if (!acceptsExtension(ext)) return WriteResult::FILE_NOT_HANDLED;

            if (!img.isDataContiguous())
            {
                OSG_WARN<<"Warning: Writing of image data, that is non contiguous, is not supported by JPEG2000 plugin."<<std::endl;
                return WriteResult::ERROR_IN_WRITING_FILE;
            }

            jas_image_cmptparm_t cmptparms[4];
            jas_image_cmptparm_t *cmptparm;

            int internalFormat = osg::Image::computeNumComponents(img.getPixelFormat());

            jas_stream_t* mem = jas_stream_memopen((char*)img.data(), internalFormat*img.s()*img.t());

            /* Create an image of the correct size. */
            jas_image_t* jimage;
            int i;
            for (i = 0, cmptparm = cmptparms; i < internalFormat; ++i, ++cmptparm) {
                cmptparm->tlx = 0;
                cmptparm->tly = 0;
                cmptparm->hstep = 1;
                cmptparm->vstep = 1;
                cmptparm->width = img.s();
                cmptparm->height = img.t();
                cmptparm->prec = 8;
                cmptparm->sgnd = 0;
            }
            if (!(jimage = jas_image_create(internalFormat, cmptparms, JAS_CLRSPC_UNKNOWN))) {
                return WriteResult::ERROR_IN_WRITING_FILE;
            }

            if(internalFormat == 1)
            {
                jas_image_setclrspc(jimage, JAS_CLRSPC_GENGRAY);
                jas_image_setcmpttype(jimage, 0, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_GRAY_Y));
            }
            else if(internalFormat == 2)
            {
                jas_image_setclrspc(jimage, JAS_CLRSPC_GENGRAY);
                jas_image_setcmpttype(jimage, 0, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_GRAY_Y));
                jas_image_setcmpttype(jimage, 1, JAS_IMAGE_CT_COLOR(JAS_IMAGE_CT_OPACITY));
            }
            else if(internalFormat == 3)
            {
                jas_image_setclrspc(jimage, JAS_CLRSPC_SRGB);
                jas_image_setcmpttype(jimage, 0, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_R));
                jas_image_setcmpttype(jimage, 1, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_G));
                jas_image_setcmpttype(jimage, 2, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_B));
            }
            else if(internalFormat == 4)
            {
                jas_image_setclrspc(jimage, JAS_CLRSPC_SRGB);
                jas_image_setcmpttype(jimage, 0, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_R));
                jas_image_setcmpttype(jimage, 1, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_G));
                jas_image_setcmpttype(jimage, 2, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_B));
                jas_image_setcmpttype(jimage, 3, JAS_IMAGE_CT_COLOR(JAS_IMAGE_CT_OPACITY));
            }

            getdata(mem, jimage);

            FILE * fileHandle = osgDB::fopen(fileName.c_str(), "wb");
            if (!fileHandle) {
                return WriteResult::ERROR_IN_WRITING_FILE;
            }
            jas_stream_t* out = jas_stream_freopen(fileName.c_str(), "wb", fileHandle);        // Replacement for jas_stream_fopen() to be able to support UTF8
            if (!out) {
                fclose(fileHandle);
                return WriteResult::ERROR_IN_WRITING_FILE;
            }

            char* opt = 0;
            if(options)
            {
                opt = new char[options->getOptionString().size() + 1];
                strcpy(opt, options->getOptionString().c_str());
            }
            jas_image_encode(jimage, out, _fmt_jp2,  opt);
            if(opt) delete[] opt;

            jas_stream_flush(out);

            jas_stream_close(out);
            jas_image_destroy(jimage);
            fclose(fileHandle);

            return WriteResult::FILE_SAVED;
        }