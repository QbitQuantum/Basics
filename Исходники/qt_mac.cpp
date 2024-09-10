QFont qfontForThemeFont(ThemeFontID themeID)
{
#ifndef QT_MAC_USE_COCOA
    static const ScriptCode Script = smRoman;
    Str255 f_name;
    SInt16 f_size;
    Style f_style;
    GetThemeFont(themeID, Script, f_name, &f_size, &f_style);
    extern QString qt_mac_from_pascal_string(const Str255); //qglobal.cpp
    return QFont(qt_mac_from_pascal_string(f_name), f_size,
                 (f_style & ::bold) ? QFont::Bold : QFont::Normal,
                 (bool)(f_style & ::italic));
#else
    QCFType<CTFontRef> ctfont = CopyCTThemeFont(themeID);
    QString familyName = QCFString(CTFontCopyFamilyName(ctfont));
    QCFType<CFDictionaryRef> dict = CTFontCopyTraits(ctfont);
    CFNumberRef num = static_cast<CFNumberRef>(CFDictionaryGetValue(dict, kCTFontWeightTrait));
    float fW;
    CFNumberGetValue(num, kCFNumberFloat32Type, &fW);
    QFont::Weight wght = fW > 0. ? QFont::Bold : QFont::Normal;
    num = static_cast<CFNumberRef>(CFDictionaryGetValue(dict, kCTFontSlantTrait));
    CFNumberGetValue(num, kCFNumberFloatType, &fW);
    bool italic = (fW != 0.0);
    return QFont(familyName, CTFontGetSize(ctfont), wght, italic);
#endif
}