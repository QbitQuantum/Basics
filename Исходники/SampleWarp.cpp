    WarpView() {
        SkBitmap bm;
//        SkImageDecoder::DecodeFile("/skimages/marker.png", &bm);
        SkImageDecoder::DecodeFile("/skimages/logo.gif", &bm);
   //     SkImageDecoder::DecodeFile("/beach_shot.JPG", &bm);
        fBitmap = bm;

        SkRect bounds, texture;
        texture.set(0, 0, SkIntToScalar(fBitmap.width()),
                    SkIntToScalar(fBitmap.height()));
        bounds = texture;

//        fMesh.init(bounds, fBitmap.width() / 40, fBitmap.height() / 40, texture);
        fMesh.init(bounds, fBitmap.width()/16, fBitmap.height()/16, texture);
        fOrig = fMesh;

        fP0.set(0, 0);
        fP1 = fP0;

        fMatrix.setScale(2, 2);
        fMatrix.invert(&fInverse);
    }