static QFontEngine *loadEngine(int script, const QFontDef &request,
                               HDC fontHdc, int dpi, bool rawMode,
                               const QtFontDesc *desc,
                               const QStringList &family_list)
{
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));

    bool useDevice = (request.styleStrategy & QFont::PreferDevice) && fontHdc;

    HDC hdc = shared_dc();
    QString font_name = desc != 0 ? desc->family->name : request.family;

    if (useDevice) {
        hdc = fontHdc;
        font_name = request.family;
    }

    bool stockFont = false;
    bool preferClearTypeAA = false;

    HFONT hfont = 0;


#if !defined(QT_NO_DIRECTWRITE)
    bool useDirectWrite = (request.hintingPreference == QFont::PreferNoHinting)
                       || (request.hintingPreference == QFont::PreferVerticalHinting);
    IDWriteFont *directWriteFont = 0;
#else
    bool useDirectWrite = false;
#endif

    if (rawMode) {                        // will choose a stock font
        int f, deffnt = SYSTEM_FONT;
        QString fam = desc != 0 ? desc->family->name.toLower() : request.family.toLower();
        if (fam == QLatin1String("default"))
            f = deffnt;
        else if (fam == QLatin1String("system"))
            f = SYSTEM_FONT;
#ifndef Q_WS_WINCE
        else if (fam == QLatin1String("system_fixed"))
            f = SYSTEM_FIXED_FONT;
        else if (fam == QLatin1String("ansi_fixed"))
            f = ANSI_FIXED_FONT;
        else if (fam == QLatin1String("ansi_var"))
            f = ANSI_VAR_FONT;
        else if (fam == QLatin1String("device_default"))
            f = DEVICE_DEFAULT_FONT;
        else if (fam == QLatin1String("oem_fixed"))
            f = OEM_FIXED_FONT;
#endif
        else if (fam[0] == QLatin1Char('#'))
            f = fam.right(fam.length()-1).toInt();
        else
            f = deffnt;
        hfont = (HFONT)GetStockObject(f);
        if (!hfont) {
            qErrnoWarning("QFontEngine::loadEngine: GetStockObject failed");
            hfont = systemFont();
        }
        stockFont = true;
    } else {

        int hint = FF_DONTCARE;
        switch (request.styleHint) {
            case QFont::Helvetica:
                hint = FF_SWISS;
                break;
            case QFont::Times:
                hint = FF_ROMAN;
                break;
            case QFont::Courier:
                hint = FF_MODERN;
                break;
            case QFont::OldEnglish:
                hint = FF_DECORATIVE;
                break;
            case QFont::System:
                hint = FF_MODERN;
                break;
            default:
                break;
        }

        lf.lfHeight = -qRound(request.pixelSize);
        lf.lfWidth                = 0;
        lf.lfEscapement        = 0;
        lf.lfOrientation        = 0;
        if (desc == 0 || desc->style->key.weight == 50)
            lf.lfWeight = FW_DONTCARE;
        else
            lf.lfWeight = (desc->style->key.weight*900)/99;
        lf.lfItalic         = (desc != 0 && desc->style->key.style != QFont::StyleNormal);
        lf.lfCharSet        = DEFAULT_CHARSET;

        int strat = OUT_DEFAULT_PRECIS;
        if (request.styleStrategy & QFont::PreferBitmap) {
            strat = OUT_RASTER_PRECIS;
#ifndef Q_WS_WINCE
        } else if (request.styleStrategy & QFont::PreferDevice) {
            strat = OUT_DEVICE_PRECIS;
        } else if (request.styleStrategy & QFont::PreferOutline) {
            strat = OUT_OUTLINE_PRECIS;
        } else if (request.styleStrategy & QFont::ForceOutline) {
            strat = OUT_TT_ONLY_PRECIS;
#endif
        }

        lf.lfOutPrecision   = strat;

        int qual = DEFAULT_QUALITY;

        if (request.styleStrategy & QFont::PreferMatch)
            qual = DRAFT_QUALITY;
#ifndef Q_WS_WINCE
        else if (request.styleStrategy & QFont::PreferQuality)
            qual = PROOF_QUALITY;
#endif

        if (request.styleStrategy & QFont::PreferAntialias) {
            if (QSysInfo::WindowsVersion >= QSysInfo::WV_XP) {
                qual = CLEARTYPE_QUALITY;
                preferClearTypeAA = true;
            } else {
                qual = ANTIALIASED_QUALITY;
            }
        } else if (request.styleStrategy & QFont::NoAntialias) {
            qual = NONANTIALIASED_QUALITY;
        }

        lf.lfQuality        = qual;

        lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
        lf.lfPitchAndFamily = DEFAULT_PITCH | hint;

        QString fam = font_name;

        if(fam.isEmpty())
            fam = QLatin1String("MS Sans Serif");

        if ((fam == QLatin1String("MS Sans Serif"))
            && (request.style == QFont::StyleItalic || (-lf.lfHeight > 18 && -lf.lfHeight != 24))) {
            fam = QLatin1String("Arial"); // MS Sans Serif has bearing problems in italic, and does not scale
        }
        if (fam == QLatin1String("Courier") && !(request.styleStrategy & QFont::PreferBitmap))
            fam = QLatin1String("Courier New");

        memcpy(lf.lfFaceName, fam.utf16(), sizeof(wchar_t) * qMin(fam.length() + 1, 32));  // 32 = Windows hard-coded

        hfont = CreateFontIndirect(&lf);
        if (!hfont)
            qErrnoWarning("QFontEngine::loadEngine: CreateFontIndirect failed");

        stockFont = (hfont == 0);
        bool ttf = false;
        int avWidth = 0;
        BOOL res;
        HGDIOBJ oldObj = SelectObject(hdc, hfont);

        TEXTMETRIC tm;
        res = GetTextMetrics(hdc, &tm);
        avWidth = tm.tmAveCharWidth;
        ttf = tm.tmPitchAndFamily & TMPF_TRUETYPE;
        SelectObject(hdc, oldObj);

        if (!ttf || !useDirectWrite) {
            useDirectWrite = false;

            if (hfont && (!ttf || request.stretch != 100)) {
                DeleteObject(hfont);
                if (!res)
                    qErrnoWarning("QFontEngine::loadEngine: GetTextMetrics failed");
                lf.lfWidth = avWidth * request.stretch/100;
                hfont = CreateFontIndirect(&lf);
                if (!hfont)
                    qErrnoWarning("QFontEngine::loadEngine: CreateFontIndirect with stretch failed");
            }

#ifndef Q_WS_WINCE
            if (hfont == 0) {
                hfont = (HFONT)GetStockObject(ANSI_VAR_FONT);
                stockFont = true;
            }
#else
            if (hfont == 0) {
                hfont = (HFONT)GetStockObject(SYSTEM_FONT);
                stockFont = true;
            }
#endif

        }

#if !defined(QT_NO_DIRECTWRITE)
        else {
            // Default to false for DirectWrite (and re-enable once/if everything
            // turns out okay)
            useDirectWrite = false;

            QFontDatabasePrivate *db = privateDb();
            if (db->directWriteFactory == 0) {
                HRESULT hr = DWriteCreateFactory(
                            DWRITE_FACTORY_TYPE_SHARED,
                            __uuidof(IDWriteFactory),
                            reinterpret_cast<IUnknown **>(&db->directWriteFactory)
                            );
                if (FAILED(hr)) {
                    qErrnoWarning("QFontEngine::loadEngine: DWriteCreateFactory failed");
                } else {
                    hr = db->directWriteFactory->GetGdiInterop(&db->directWriteGdiInterop);
                    if (FAILED(hr))
                        qErrnoWarning("QFontEngine::loadEngine: GetGdiInterop failed");
                }
            }

            if (db->directWriteGdiInterop != 0) {
                QString nameSubstitute = fontNameSubstitute(QString::fromWCharArray(lf.lfFaceName));
                memcpy(lf.lfFaceName, nameSubstitute.utf16(),
                       sizeof(wchar_t) * qMin(nameSubstitute.length() + 1, LF_FACESIZE));

                HRESULT hr = db->directWriteGdiInterop->CreateFontFromLOGFONT(
                            &lf,
                            &directWriteFont);
                if (FAILED(hr)) {
#ifndef QT_NO_DEBUG
                    qErrnoWarning("QFontEngine::loadEngine: CreateFontFromLOGFONT failed "
                                  "for %ls (0x%lx)",
                                  lf.lfFaceName, hr);
#endif
                } else {
                    DeleteObject(hfont);
                    useDirectWrite = true;
                }
            }
        }
#endif

    }

    QFontEngine *fe = 0;
    if (!useDirectWrite)  {
        QFontEngineWin *few = new QFontEngineWin(font_name, hfont, stockFont, lf);
        if (preferClearTypeAA)
            few->glyphFormat = QFontEngineGlyphCache::Raster_RGBMask;

        // Also check for OpenType tables when using complex scripts
        // ### TODO: This only works for scripts that require OpenType. More generally
        // for scripts that do not require OpenType we should just look at the list of
        // supported writing systems in the font's OS/2 table.
        if (scriptRequiresOpenType(script)) {
            HB_Face hbFace = few->harfbuzzFace();
            if (!hbFace || !hbFace->supported_scripts[script]) {
                FM_DEBUG("  OpenType support missing for script\n");
                delete few;
                return 0;
            }
        }

        initFontInfo(few, request, fontHdc, dpi);
        fe = few;
    }

#if !defined(QT_NO_DIRECTWRITE)
    else {
        QFontDatabasePrivate *db = privateDb();

        IDWriteFontFace *directWriteFontFace = NULL;
        HRESULT hr = directWriteFont->CreateFontFace(&directWriteFontFace);
        if (SUCCEEDED(hr)) {
            QFontEngineDirectWrite *fedw = new QFontEngineDirectWrite(db->directWriteFactory,
                                                                      directWriteFontFace,
                                                                      request.pixelSize);

            initFontInfo(fedw, request, dpi, directWriteFont);

            fe = fedw;
        } else {
            qErrnoWarning(hr, "QFontEngine::loadEngine: CreateFontFace failed");
        }
    }

    if (directWriteFont != 0)
        directWriteFont->Release();
#endif

    if(script == QUnicodeTables::Common
       && !(request.styleStrategy & QFont::NoFontMerging)
       && desc != 0
       && !(desc->family->writingSystems[QFontDatabase::Symbol] & QtFontFamily::Supported)) {
        if(!tryFonts) {
            LANGID lid = GetUserDefaultLangID();
            switch( lid&0xff ) {
            case LANG_CHINESE: // Chinese (Taiwan)
                if ( lid == 0x0804 ) // Taiwan
                    tryFonts = ch_TW_tryFonts;
                else
                    tryFonts = ch_CN_tryFonts;
                break;
            case LANG_JAPANESE:
                tryFonts = jp_tryFonts;
                break;
            case LANG_KOREAN:
                tryFonts = kr_tryFonts;
                break;
            default:
                tryFonts = other_tryFonts;
                break;
            }
        }
        QStringList fm = QFontDatabase().families();
        QStringList list = family_list;
        const char **tf = tryFonts;
        while(tf && *tf) {
            if(fm.contains(QLatin1String(*tf)))
                list << QLatin1String(*tf);
            ++tf;
        }
        QFontEngine *mfe = new QFontEngineMultiWin(fe, list);
        mfe->fontDef = fe->fontDef;
        fe = mfe;
    }
    return fe;
}