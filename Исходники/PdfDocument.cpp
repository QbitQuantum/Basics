static jlong nativeStartPage(JNIEnv* env, jobject thiz, jlong documentPtr,
        jint pageWidth, jint pageHeight,
        jint contentLeft, jint contentTop, jint contentRight, jint contentBottom) {
    PdfDocument* document = reinterpret_cast<PdfDocument*>(documentPtr);
    SkCanvas* canvas = document->startPage(pageWidth, pageHeight,
            contentLeft, contentTop, contentRight, contentBottom);
    return reinterpret_cast<jlong>(Canvas::create_canvas(canvas));
}