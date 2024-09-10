static void*
imdecode_( const Vector<uchar>& buf, int flags, int hdrtype, Mat* mat=0 )
{
    IplImage* image = 0;
    CvMat *matrix = 0;
    Mat temp, *data = &temp;
    char fnamebuf[L_tmpnam];
    const char* filename = 0;

    ImageDecoder decoder = findDecoder(buf);
    if( !decoder.obj )
        return 0;

    if( !decoder->setSource(buf) )
    {
        filename = tmpnam(fnamebuf);
        FILE* f = fopen( filename, "wb" );
        if( !f )
            return 0;
        fwrite( &buf[0], 1, buf.size(), f );
        fclose(f);
        decoder->setSource(filename);
    }

    if( !decoder->readHeader() )
    {
        if( filename )
            unlink(filename);
        return 0;
    }

    CvSize size;
    size.width = decoder->width();
    size.height = decoder->height();

    int type = decoder->type();
    if( flags != -1 )
    {
        if( (flags & CV_LOAD_IMAGE_ANYDEPTH) == 0 )
            type = CV_MAKETYPE(CV_8U, CV_MAT_CN(type));

        if( (flags & CV_LOAD_IMAGE_COLOR) != 0 ||
           ((flags & CV_LOAD_IMAGE_ANYCOLOR) != 0 && CV_MAT_CN(type) > 1) )
            type = CV_MAKETYPE(CV_MAT_DEPTH(type), 3);
        else
            type = CV_MAKETYPE(CV_MAT_DEPTH(type), 1);
    }

    if( hdrtype == LOAD_CVMAT || hdrtype == LOAD_MAT )
    {
        if( hdrtype == LOAD_CVMAT )
        {
            matrix = cvCreateMat( size.height, size.width, type );
            temp = cvarrToMat(matrix);
        }
        else
        {
            mat->create( size.height, size.width, type );
            data = mat;
        }
    }
    else
    {
        image = cvCreateImage( size, cvIplDepth(type), CV_MAT_CN(type) );
        temp = cvarrToMat(image);
    }

    bool code = decoder->readData( *data );
    if( filename )
        unlink(filename);

    if( !code )
    {
        cvReleaseImage( &image );
        cvReleaseMat( &matrix );
        if( mat )
            mat->release();
        return 0;
    }

    return hdrtype == LOAD_CVMAT ? (void*)matrix :
        hdrtype == LOAD_IMAGE ? (void*)image : (void*)mat;
}