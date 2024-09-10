CQuestionManager::Question CQuestionManager::GenOneQuestion()
{
    Question ques = { { 0 }, 0 };
    CFileListManager &file_manager = GetInst( CFileListManager );
    int r = 0;

    // alpha image
    CImage img_alpha;
    CreateImgFromBuffer( file_manager.GetAlpha(), img_alpha );

    // 1.generate the background.
    CImage back;
    CreateImgFromBuffer( file_manager.GetRandBack(), back );
    r = random( 3 );
    CImage *img_cover;
    for( int i = 0; i < r; ++ i )
    {
        img_cover = MP_NEW CImage();
        CreateImgFromBuffer( file_manager.GetRandBack(), *img_cover );
        back.AlphaBlend( img_cover, 0, 0, ( random( 55 ) + 100 ) / 255.0f );
        MP_DELETE(img_cover);
    }

    // 2.generate small pictures.
    ques.answer = BlendSmallImage( back, img_alpha );

    // 3.covert the image to raw buffer.
    if( !back.ExportJpegToMemory( (BYTE*&) ques.data.buf, (DWORD&) ques.data.size, 85 ) )
    {
        ques.data.buf = 0;
        ques.data.size = 0;
        PutoutLog( LOG_FILE, LT_ERROR, "Export jpeg failed." );
    }

    DumpImage( &back );
    return ques;
}