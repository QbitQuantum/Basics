void EraRules::initCurrentEra() {
    UDate now = ucal_getNow();
    int year, month0, dom, dow, doy, mid;
    Grego::timeToFields(now, year, month0, dom, dow, doy, mid);
    int currentEncodedDate = encodeDate(year, month0 + 1 /* changes to 1-base */, dom);
    int eraIdx = numEras - 1;
    while (eraIdx > 0) {
        if (currentEncodedDate >= startDates[eraIdx]) {
            break;
        }
        eraIdx--;
    }
    // Note: current era could be before the first era.
    // In this case, this implementation returns the first era index (0).
    currentEra = eraIdx;}