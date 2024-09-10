static inline UTransliterator *utrans_find(CFStringRef transform, UTransDirection dir, UErrorCode *error) {
    UEnumeration *uenum = NULL;
    UTransliterator *trans = NULL;
    do {
        uenum = utrans_openIDs(error);
        if (U_FAILURE(*error)) {
            DEBUG_LOG("%s", u_errorName(*error));
            break;
        }

        int32_t count = uenum_count(uenum, error);
        if (U_FAILURE(*error)) {
            DEBUG_LOG("%s", u_errorName(*error));
            break;
        }
        int32_t trans_idx = 0;
        while (trans_idx < count && trans == NULL) {
            int32_t idLen = 0;
            const UChar *uid = uenum_unext(uenum, &idLen, error);
            if (U_FAILURE(*error)) {
                DEBUG_LOG("%s", u_errorName(*error));
                break;
            }
            // this seems rather unlikely since we should have already broken
            // by the trans_idx exceeding the count
            if (uid == NULL) {
                break;
            }

            CFStringRef name = CFStringCreateWithCharactersNoCopy(kCFAllocatorDefault, uid, idLen, kCFAllocatorNull);
            // It would have been nice if these stirng constants were actually defined somewhere in icu, but sadly they are runtime metadata...
            if ((CFEqual(name, CFSTR("Any-Remove")) && CFEqual(transform, kCFStringTransformStripCombiningMarks)) ||
                (CFEqual(name, CFSTR("Any-Latin")) && CFEqual(transform, kCFStringTransformToLatin)) ||
                (CFEqual(name, CFSTR("Latin-Katakana")) && CFEqual(transform, kCFStringTransformLatinKatakana)) ||
                (CFEqual(name, CFSTR("Latin-Hiragana")) && CFEqual(transform, kCFStringTransformLatinHiragana)) ||
                (CFEqual(name, CFSTR("Hiragana-Katakana")) && CFEqual(transform, kCFStringTransformHiraganaKatakana)) ||
                (CFEqual(name, CFSTR("Latin-Hangul")) && CFEqual(transform, kCFStringTransformLatinHangul)) ||
                (CFEqual(name, CFSTR("Latin-Arabic")) && CFEqual(transform, kCFStringTransformLatinArabic)) ||
                (CFEqual(name, CFSTR("Latin-Hebrew")) && CFEqual(transform, kCFStringTransformLatinHebrew)) ||
                (CFEqual(name, CFSTR("Latin-Thai")) && CFEqual(transform, kCFStringTransformLatinThai)) ||
                (CFEqual(name, CFSTR("Latin-Cyrillic")) && CFEqual(transform, kCFStringTransformLatinCyrillic)) ||
                (CFEqual(name, CFSTR("Latin-Greek")) && CFEqual(transform, kCFStringTransformLatinGreek)) ||
                (CFEqual(name, CFSTR("Any-Hex/XML")) && CFEqual(transform, kCFStringTransformToXMLHex)) ||
                (CFEqual(name, CFSTR("Any-Name")) && CFEqual(transform, kCFStringTransformToUnicodeName)) ||
                (CFEqual(name, CFSTR("Accents-Any")) && CFEqual(transform, kCFStringTransformStripDiacritics))) {
                trans = utrans_openU(uid, idLen, dir, NULL, 0, NULL, error);
            }
            CFRelease(name);
            trans_idx++;
        }
    } while (0);

    if (uenum != NULL) {
        uenum_reset(uenum, error);
        uenum_close(uenum);
    }

    if (trans == NULL && (CFEqual(transform, kCFStringTransformStripCombiningMarks) ||
                          CFEqual(transform, kCFStringTransformToLatin) ||
                          CFEqual(transform, kCFStringTransformLatinKatakana) ||
                          CFEqual(transform, kCFStringTransformLatinHiragana) ||
                          CFEqual(transform, kCFStringTransformHiraganaKatakana) ||
                          CFEqual(transform, kCFStringTransformLatinHangul) ||
                          CFEqual(transform, kCFStringTransformLatinArabic) ||
                          CFEqual(transform, kCFStringTransformLatinHebrew) ||
                          CFEqual(transform, kCFStringTransformLatinCyrillic) ||
                          CFEqual(transform, kCFStringTransformLatinGreek) ||
                          CFEqual(transform, kCFStringTransformToXMLHex) ||
                          CFEqual(transform, kCFStringTransformToUnicodeName) ||
                          CFEqual(transform, kCFStringTransformStripDiacritics))) {
        static dispatch_once_t once = 0L;
        dispatch_once(&once, ^{
            RELEASE_LOG("Unable to find transliterators in icu data: likely this is from not including the Transliterators section in building your icu.dat file");
        });
    }