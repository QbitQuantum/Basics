FontCustomPlatformData* createFontCustomPlatformData(SharedBuffer* buffer)
{
    ASSERT_ARG(buffer, buffer);
    ASSERT(T2embedLibrary());

    // Get CG to create the font.
    CGDataProviderDirectAccessCallbacks callbacks = { &getData, &releaseData, &getBytesWithOffset, NULL };
    RetainPtr<CGDataProviderRef> dataProvider(AdoptCF, CGDataProviderCreateDirectAccess(buffer, buffer->size(), &callbacks));
    CGFontRef cgFont = CGFontCreateWithDataProvider(dataProvider.get());
    if (!cgFont)
        return 0;

    // Introduce the font to GDI. AddFontMemResourceEx cannot be used, because it will pollute the process's
    // font namespace (Windows has no API for creating an HFONT from data without exposing the font to the
    // entire process first). TTLoadEmbeddedFont lets us override the font family name, so using a unique name
    // we avoid namespace collisions.

    String fontName = createUniqueFontName();

    // TTLoadEmbeddedFont works only with Embedded OpenType (.eot) data, so we need to create an EOT header
    // and prepend it to the font data.
    Vector<UInt8, 512> eotHeader;
    if (!getEOTHeader(buffer, eotHeader)) {
        CGFontRelease(cgFont);
        return 0;
    }

    HANDLE fontReference;
    ULONG privStatus;
    ULONG status;
    EOTStream eotStream(eotHeader, buffer);

    LONG loadEmbeddedFontResult = TTLoadEmbeddedFont(&fontReference, TTLOAD_PRIVATE, &privStatus, LICENSE_PREVIEWPRINT, &status, readEmbedProc, &eotStream, const_cast<LPWSTR>(fontName.charactersWithNullTermination()), 0, 0);
    if (loadEmbeddedFontResult != E_NONE) {
        CGFontRelease(cgFont);
        return 0;
    }

    return new FontCustomPlatformData(cgFont, fontReference);
}