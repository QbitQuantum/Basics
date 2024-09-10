BOOL IsUnicodeFullWidth(
    IN WCHAR wch
    )
{
    if (0x20 <= wch && wch <= 0x7e)
        /* ASCII */
        return FALSE;
    else if (0x3041 <= wch && wch <= 0x3094)
        /* Hiragana */
        return TRUE;
    else if (0x30a1 <= wch && wch <= 0x30f6)
        /* Katakana */
        return TRUE;
    else if (0x3105 <= wch && wch <= 0x312c)
        /* Bopomofo */
        return TRUE;
    else if (0x3131 <= wch && wch <= 0x318e)
        /* Hangul Elements */
        return TRUE;
    else if (0xac00 <= wch && wch <= 0xd7a3)
        /* Korean Hangul Syllables */
        return TRUE;
    else if (0xff01 <= wch && wch <= 0xff5e)
        /* Fullwidth ASCII variants */
        return TRUE;
    else if (0xff61 <= wch && wch <= 0xff9f)
        /* Halfwidth Katakana variants */
        return FALSE;
    else if ( (0xffa0 <= wch && wch <= 0xffbe) ||
              (0xffc2 <= wch && wch <= 0xffc7) ||
              (0xffca <= wch && wch <= 0xffcf) ||
              (0xffd2 <= wch && wch <= 0xffd7) ||
              (0xffda <= wch && wch <= 0xffdc)   )
        /* Halfwidth Hangule variants */
        return FALSE;
    else if (0xffe0 <= wch && wch <= 0xffe6)
        /* Fullwidth symbol variants */
        return TRUE;
    else if (0x4e00 <= wch && wch <= 0x9fa5)
        /* Han Ideographic */
        return TRUE;
    else if (0xf900 <= wch && wch <= 0xfa2d)
        /* Han Ideographic Compatibility */
        return TRUE;
    else
    {
#if 0
        /*
         * Hack this block for I don't know FONT of Console Window.
         *
         * If you would like perfect result from IsUnicodeFullWidth routine,
         * then you should enable this block and
         * you should know FONT of Console Window.
         */

        INT Width;
        TEXTMETRIC tmi;

        /* Unknown character */

        GetTextMetricsW(hDC, &tmi);
        if (IS_ANY_DBCS_CHARSET(tmi.tmCharSet))
            tmi.tmMaxCharWidth /= 2;

        GetCharWidth32(hDC, wch, wch, &Width);
        if (Width == tmi.tmMaxCharWidth)
            return FALSE;
        else if (Width == tmi.tmMaxCharWidth*2)
            return TRUE;
#else
        ULONG MultiByteSize;

        RtlUnicodeToMultiByteSize(&MultiByteSize, &wch, sizeof(WCHAR));
        if (MultiByteSize == 2)
            return TRUE ;
        else
            return FALSE ;
#endif
    }
    ASSERT(FALSE);
    return FALSE;
#if 0
    ULONG MultiByteSize;

    RtlUnicodeToMultiByteSize(&MultiByteSize, &wch, sizeof(WCHAR));
    if (MultiByteSize == 2)
        return TRUE ;
    else
        return FALSE ;
#endif
}