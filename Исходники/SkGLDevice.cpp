SkGLDevice::TexCache* SkGLDevice::setupGLPaintShader(const SkPaint& paint) {
    SkGL::SetPaint(paint);
    
    SkShader* shader = paint.getShader();
    if (NULL == shader) {
        return NULL;
    }
    
    if (!shader->setContext(this->accessBitmap(false), paint, this->matrix())) {
        return NULL;
    }
    
    SkBitmap bitmap;
    SkMatrix matrix;
    SkShader::TileMode tileModes[2];
    if (!shader->asABitmap(&bitmap, &matrix, tileModes)) {
        return NULL;
    }
    
    bitmap.lockPixels();
    if (!bitmap.readyToDraw()) {
        return NULL;
    }
    
    // see if we've already cached the bitmap from the shader
    SkPoint max;
    GLuint name;
    TexCache* cache = SkGLDevice::LockTexCache(bitmap, &name, &max);
    // the lock has already called glBindTexture for us
    SkGL::SetTexParams(paint.isFilterBitmap(), tileModes[0], tileModes[1]);
    
    // since our texture coords will be in local space, we wack the texture
    // matrix to map them back into 0...1 before we load it
    SkMatrix localM;
    if (shader->getLocalMatrix(&localM)) {
        SkMatrix inverse;
        if (localM.invert(&inverse)) {
            matrix.preConcat(inverse);
        }
    }
    
    matrix.postScale(max.fX / bitmap.width(), max.fY / bitmap.height());
    glMatrixMode(GL_TEXTURE);
    SkGL::LoadMatrix(matrix);
    glMatrixMode(GL_MODELVIEW);
    
    // since we're going to use a shader/texture, we don't want the color,
    // just its alpha
    SkGL::SetAlpha(paint.getAlpha());
    // report that we have setup the texture
    return cache;
}