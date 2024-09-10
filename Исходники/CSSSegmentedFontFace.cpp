void CSSSegmentedFontFace::loadFont(const FontDescription& fontDescription, PassRefPtr<LoadFontCallback> callback)
{
    getFontData(fontDescription); // Kick off the load.

    if (callback) {
        if (isLoading())
            m_callbacks.append(callback);
        else if (checkFont())
            callback->notifyLoaded(this);
        else
            callback->notifyError(this);
    }
}