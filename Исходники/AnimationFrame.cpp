    AnimationFrame AnimationFrame::getClipped(const RectF& rect) const
    {
        AnimationFrame f = *this;
        float w = (float)_diffuse.base->getWidth();
        float h = (float)_diffuse.base->getHeight();

        f._destRect.clip(rect);
        if (f._destRect.isEmpty())
            f._destRect = RectF(0, 0, 0, 0);


        RectF srcRect = _srcRect * Vector2(w, h);

        float sc = 1.0f;//(float)srcRect.getWidth() / f._destRect.getWidth();
        if (_resAnim)
            sc = _resAnim->getScaleFactor();


        f._srcRect.pos = srcRect.pos - (_destRect.pos - f._destRect.pos) * sc;
        f._srcRect.size = srcRect.size - (_destRect.size - f._destRect.size) * sc;
        f._srcRect = f._srcRect / Vector2(w, h);

        f._frameSize = rect.size;
        f._destRect.pos -= rect.pos;

        return f;
    }