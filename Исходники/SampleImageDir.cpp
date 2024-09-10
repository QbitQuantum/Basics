static void drawmarshmallow(SkCanvas* canvas) {
    SkBitmap bitmap;
    SkPaint paint;
    SkRect r;
    SkMatrix m;

    SkImageDecoder::DecodeFile("/Users/reed/Downloads/3elfs.jpg", &bitmap);
    if (!bitmap.pixelRef()) {
        return;
    }

    SkShader* s = SkShader::CreateBitmapShader(bitmap,
                                               SkShader::kRepeat_TileMode,
                                               SkShader::kRepeat_TileMode);
    paint.setShader(s)->unref();
    m.setTranslate(SkIntToScalar(250), SkIntToScalar(134));
    s->setLocalMatrix(m);

    r.set(SkIntToScalar(250),
          SkIntToScalar(134),
          SkIntToScalar(250 + 449),
          SkIntToScalar(134 + 701));
    paint.setFlags(2);

    canvas->drawRect(r, paint);
}