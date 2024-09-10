void
IntlTestNumberFormatAPI::testRegistration()
{
#if !UCONFIG_NO_SERVICE
    UErrorCode status = U_ZERO_ERROR;

    NumberFormat* f0 = NumberFormat::createInstance(SWAP_LOC, status);
    NumberFormat* f1 = NumberFormat::createInstance(SRC_LOC, status);
    NumberFormat* f2 = NumberFormat::createCurrencyInstance(SRC_LOC, status);
    URegistryKey key = NumberFormat::registerFactory(new NFTestFactory(), status);
    NumberFormat* f3 = NumberFormat::createCurrencyInstance(SRC_LOC, status);
    NumberFormat* f3a = NumberFormat::createCurrencyInstance(SRC_LOC, status);
    NumberFormat* f4 = NumberFormat::createInstance(SRC_LOC, status);

    StringEnumeration* locs = NumberFormat::getAvailableLocales();

    UNumberFormat* uf3 = unum_open(UNUM_CURRENCY, NULL, 0, SRC_LOC.getName(),NULL, &status);
    UNumberFormat* uf4 = unum_open(UNUM_DEFAULT, NULL, 0, SRC_LOC.getName(), NULL, &status);

    const UnicodeString* res;
    for (res = locs->snext(status); res; res = locs->snext(status)) {
        logln(*res); // service is still in synch
    }

    NumberFormat::unregister(key, status); // restore for other tests
    NumberFormat* f5 = NumberFormat::createCurrencyInstance(SRC_LOC, status);
    UNumberFormat* uf5 = unum_open(UNUM_CURRENCY, NULL, 0, SRC_LOC.getName(),NULL, &status);

    if (U_FAILURE(status)) {
        dataerrln("Error creating instnaces.");
        return;
    } else {
        float n = 1234.567f;
        UnicodeString res0, res1, res2, res3, res4, res5;
        UChar ures3[50];
        UChar ures4[50];
        UChar ures5[50];

        f0->format(n, res0);
        f1->format(n, res1);
        f2->format(n, res2);
        f3->format(n, res3);
        f4->format(n, res4);
        f5->format(n, res5);

        unum_formatDouble(uf3, n, ures3, 50, NULL, &status);
        unum_formatDouble(uf4, n, ures4, 50, NULL, &status);
        unum_formatDouble(uf5, n, ures5, 50, NULL, &status);

        logln((UnicodeString)"f0 swap int: " + res0);
        logln((UnicodeString)"f1 src int: " + res1);
        logln((UnicodeString)"f2 src cur: " + res2);
        logln((UnicodeString)"f3 reg cur: " + res3);
        logln((UnicodeString)"f4 reg int: " + res4);
        logln((UnicodeString)"f5 unreg cur: " + res5);
        log("uf3 reg cur: ");
        logln(ures3);
        log("uf4 reg int: ");
        logln(ures4);
        log("uf5 ureg cur: ");
        logln(ures5);

        if (f3 == f3a) {
            errln("did not get new instance from service");
        } else {
            delete f3a;
        }
        if (res3 != res0) {
            errln("registered service did not match");
        }
        if (res4 != res1) {
            errln("registered service did not inherit");
        }
        if (res5 != res2) {
            errln("unregistered service did not match original");
        }

        if (res0 != ures3) {
            errln("registered service did not match / unum");
        }
        if (res1 != ures4) {
            errln("registered service did not inherit / unum");
        }
        if (res2 != ures5) {
            errln("unregistered service did not match original / unum");
        }
    }

    unum_close(uf5);
    delete f5;
    unum_close(uf4);
    unum_close(uf3);
    delete f4;
    delete f3;
    delete f2;
    delete f1;
    delete f0;

    for (res = locs->snext(status); res; res = locs->snext(status)) {
        errln(*res); // service should be out of synch
    }

    locs->reset(status); // now in synch again, we hope
    for (res = locs->snext(status); res; res = locs->snext(status)) {
        logln(*res);
    }

    delete locs;
#endif
}