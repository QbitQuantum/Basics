Transliterator* AnyTransliterator::getTransliterator(UScriptCode source) const {

    if (source == targetScript || source == USCRIPT_INVALID_CODE) {
        return NULL;
    }

    Transliterator* t = NULL;
    {
        Mutex m(NULL);
        t = (Transliterator*) uhash_iget(cache, (int32_t) source);
    }
    if (t == NULL) {
        UErrorCode ec = U_ZERO_ERROR;
        UnicodeString sourceName(uscript_getShortName(source), -1, US_INV);
        UnicodeString id(sourceName);
        id.append(TARGET_SEP).append(target);

        t = Transliterator::createInstance(id, UTRANS_FORWARD, ec);
        if (U_FAILURE(ec) || t == NULL) {
            delete t;

            // Try to pivot around Latin, our most common script
            id = sourceName;
            id.append(LATIN_PIVOT, -1).append(target);
            t = Transliterator::createInstance(id, UTRANS_FORWARD, ec);
            if (U_FAILURE(ec) || t == NULL) {
                delete t;
                t = NULL;
            }
        }

        if (t != NULL) {
            Transliterator *rt = NULL;
            {
                Mutex m(NULL);
                rt = static_cast<Transliterator *> (uhash_iget(cache, (int32_t) source));
                if (rt == NULL) {
                    // Common case, no race to cache this new transliterator.
                    uhash_iput(cache, (int32_t) source, t, &ec);
                } else {
                    // Race case, some other thread beat us to caching this transliterator.
                    Transliterator *temp = rt;
                    rt = t;    // Our newly created transliterator that lost the race & now needs deleting.
                    t  = temp; // The transliterator from the cache that we will return.
                }
            }
            delete rt;    // will be non-null only in case of races.
        }
    }
    return t;
}