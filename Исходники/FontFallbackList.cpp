const FontData* FontFallbackList::fontDataAt(const FontDescription& fontDescription, unsigned realizedFontIndex) const
{
    if (realizedFontIndex < m_fontList.size())
        return m_fontList[realizedFontIndex].get(); // This fallback font is already in our list.

    // Make sure we're not passing in some crazy value here.
    ASSERT(realizedFontIndex == m_fontList.size());

    if (m_familyIndex == cAllFamiliesScanned)
        return 0;

    // Ask the font cache for the font data.
    // We are obtaining this font for the first time.  We keep track of the families we've looked at before
    // in |m_familyIndex|, so that we never scan the same spot in the list twice.  getFontData will adjust our
    // |m_familyIndex| as it scans for the right font to make.
    ASSERT(FontCache::fontCache()->generation() == m_generation);
    RefPtr<FontData> result = getFontData(fontDescription, m_familyIndex);
    if (result) {
        m_fontList.append(result);
        if (result->isLoadingFallback())
            m_hasLoadingFallback = true;
    }
    return result.get();
}