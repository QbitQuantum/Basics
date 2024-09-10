    MaskedRenderer::MaskedRenderer(spNativeTexture mask, const RectF& srcRect, const RectF& destRect, const Transform& t, bool channelR) : _mask(mask)
    {
        _clipUV = ClipUV(
                      t.transform(destRect.getLeftTop()),
                      t.transform(destRect.getRightTop()),
                      t.transform(destRect.getLeftBottom()),
                      srcRect.getLeftTop(),
                      srcRect.getRightTop(),
                      srcRect.getLeftBottom());

        _clipMask = srcRect;
        Vector2 v(1.0f / mask->getWidth(), 1.0f / mask->getHeight());
        _clipMask.expand(v, v);

        _shaderFlags |= UberShaderProgram::MASK;
        if (channelR)
            _shaderFlags |= UberShaderProgram::MASK_R_CHANNEL;
    }