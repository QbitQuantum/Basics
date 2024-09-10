void CollationServiceTest::TestRegister()
{
#if !UCONFIG_NO_SERVICE
    // register a singleton
    const Locale& FR = Locale::getFrance();
    const Locale& US = Locale::getUS();
    const Locale US_FOO("en", "US", "FOO");

    UErrorCode status = U_ZERO_ERROR;

    Collator* frcol = Collator::createInstance(FR, status);
    Collator* uscol = Collator::createInstance(US, status);
    if(U_FAILURE(status)) {
        errcheckln(status, "Failed to create collators with %s", u_errorName(status));
        delete frcol;
        delete uscol;
        return;
    }

    { // try override en_US collator
        URegistryKey key = Collator::registerInstance(frcol, US, status);

        Collator* ncol = Collator::createInstance(US_FOO, status);
        if (*frcol != *ncol) {
            errln("register of french collator for en_US failed on request for en_US_FOO");
        }
        // ensure original collator's params not touched
        Locale loc = frcol->getLocale(ULOC_REQUESTED_LOCALE, status);
        if (loc != FR) {
          errln(UnicodeString("fr collator's requested locale changed to ") + loc.getName());
        }
        loc = frcol->getLocale(ULOC_VALID_LOCALE, status);
        if (loc != FR) {
          errln(UnicodeString("fr collator's valid locale changed to ") + loc.getName());
        }

        loc = ncol->getLocale(ULOC_REQUESTED_LOCALE, status);
        if (loc != US_FOO) {
            errln(UnicodeString("requested locale for en_US_FOO is not en_US_FOO but ") + loc.getName());
        }
        loc = ncol->getLocale(ULOC_VALID_LOCALE, status);
        if (loc != US) {
            errln(UnicodeString("valid locale for en_US_FOO is not en_US but ") + loc.getName());
        }
        loc = ncol->getLocale(ULOC_ACTUAL_LOCALE, status);
        if (loc != US) {
            errln(UnicodeString("actual locale for en_US_FOO is not en_US but ") + loc.getName());
        }
        delete ncol; ncol = NULL;

        if (!Collator::unregister(key, status)) {
            errln("failed to unregister french collator");
        }
        // !!! frcol pointer is now invalid !!!

        ncol = Collator::createInstance(US, status);
        if (*uscol != *ncol) {
            errln("collator after unregister does not match original");
        }
        delete ncol; ncol = NULL;
    }

    // recreate frcol
    frcol = Collator::createInstance(FR, status);

    LocalUCollatorPointer frFR(ucol_open("fr_FR", &status));

    { // try create collator for new locale
        Locale fu_FU_FOO("fu", "FU", "FOO");
        Locale fu_FU("fu", "FU", "");

        Collator* fucol = Collator::createInstance(fu_FU, status);
        URegistryKey key = Collator::registerInstance(frcol, fu_FU, status);
        Collator* ncol = Collator::createInstance(fu_FU_FOO, status);
        if (*frcol != *ncol) {
            errln("register of fr collator for fu_FU failed");
        }

        UnicodeString locName = fu_FU.getName();
        StringEnumeration* localeEnum = Collator::getAvailableLocales();
        UBool found = FALSE;
        const UnicodeString* locStr, *ls2;
        for (locStr = localeEnum->snext(status);
        !found && locStr != NULL;
        locStr = localeEnum->snext(status)) {
            //
            if (locName == *locStr) {
                found = TRUE;
            }
        }

        StringEnumeration *le2 = NULL;
        localeEnum->reset(status);
        int32_t i, count;
        count = localeEnum->count(status);
        for(i = 0; i < count; ++i) {
            if(i == count / 2) {
                le2 = localeEnum->clone();
                if(le2 == NULL || count != le2->count(status)) {
                    errln("ServiceEnumeration.clone() failed");
                    break;
                }
            }
            if(i >= count / 2) {
                locStr = localeEnum->snext(status);
                ls2 = le2->snext(status);
                if(*locStr != *ls2) {
                    errln("ServiceEnumeration.clone() failed for item %d", i);
                }
            } else {
                localeEnum->snext(status);
            }
        }

        delete localeEnum;
        delete le2;

        if (!found) {
            errln("new locale fu_FU not reported as supported locale");
        }

        UnicodeString displayName;
        Collator::getDisplayName(fu_FU, displayName);
        /* The locale display pattern for the locale ja, ko, and zh are different. */
        const UChar zh_fuFU_Array[] = { 0x0066, 0x0075, 0xff08, 0x0046, 0x0055, 0xff09, 0 };
        const UnicodeString zh_fuFU(zh_fuFU_Array);
        const Locale& defaultLocale = Locale::getDefault();
        if (displayName != "fu (FU)" &&
           ((defaultLocale == Locale::getKorean() && defaultLocale == Locale::getJapanese()) && displayName == "fu(FU)") &&
           ((defaultLocale == Locale::getChinese()) && displayName != zh_fuFU)) {
            errln(UnicodeString("found ") + displayName + " for fu_FU");
        }

        Collator::getDisplayName(fu_FU, fu_FU, displayName);
        if (displayName != "fu (FU)" &&
           ((defaultLocale == Locale::getKorean() && defaultLocale == Locale::getJapanese()) && displayName == "fu(FU)") &&
           ((defaultLocale == Locale::getChinese()) && displayName != zh_fuFU)) {
            errln(UnicodeString("found ") + displayName + " for fu_FU");
        }

        // test ucol_open
        LocalUCollatorPointer fufu(ucol_open("fu_FU_FOO", &status));
        if (fufu.isNull()) {
            errln("could not open fu_FU_FOO with ucol_open");
        } else {
            if (!ucol_equals(fufu.getAlias(), frFR.getAlias())) {
                errln("collator fufu != collator frFR");
            }
        }

        if (!Collator::unregister(key, status)) {
            errln("failed to unregister french collator");
        }
        // !!! note frcoll invalid again, but we're no longer using it

        // other collators should still work ok
        Locale nloc = ncol->getLocale(ULOC_VALID_LOCALE, status);
        if (nloc != fu_FU) {
            errln(UnicodeString("asked for nloc valid locale after close and got") + nloc.getName());
        }
        delete ncol; ncol = NULL;

        if (fufu.isValid()) {
            const char* nlocstr = ucol_getLocaleByType(fufu.getAlias(), ULOC_VALID_LOCALE, &status);
            if (uprv_strcmp(nlocstr, "fu_FU") != 0) {
                errln(UnicodeString("asked for uloc valid locale after close and got ") + nlocstr);
            }
        }

        ncol = Collator::createInstance(fu_FU, status);
        if (*fucol != *ncol) {
            errln("collator after unregister does not match original fu_FU");
        }
        delete uscol; uscol = NULL;
        delete ncol; ncol = NULL;
        delete fucol; fucol = NULL;
    }
#endif
}