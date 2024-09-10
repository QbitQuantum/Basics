/**
 * Dumb recursive implementation of permutation.
 * TODO: optimize
 * @param source the string to find permutations for
 * @return the results in a set.
 */
void U_EXPORT2 CanonicalIterator::permute(UnicodeString &source, UBool skipZeros, Hashtable *result, UErrorCode &status) {
    if(U_FAILURE(status)) {
        return;
    }
    //if (PROGRESS) printf("Permute: %s\n", UToS(Tr(source)));
    int32_t i = 0;

    // optimization:
    // if zero or one character, just return a set with it
    // we check for length < 2 to keep from counting code points all the time
    if (source.length() <= 2 && source.countChar32() <= 1) {
        UnicodeString *toPut = new UnicodeString(source);
        /* test for NULL */
        if (toPut == 0) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return;
        }
        result->put(source, toPut, status);
        return;
    }

    // otherwise iterate through the string, and recursively permute all the other characters
    UChar32 cp;
    Hashtable subpermute(status);
    if(U_FAILURE(status)) {
        return;
    }
    subpermute.setValueDeleter(uprv_deleteUObject);

    for (i = 0; i < source.length(); i += U16_LENGTH(cp)) {
        cp = source.char32At(i);
        const UHashElement *ne = NULL;
        int32_t el = UHASH_FIRST;
        UnicodeString subPermuteString = source;

        // optimization:
        // if the character is canonical combining class zero,
        // don't permute it
        if (skipZeros && i != 0 && u_getCombiningClass(cp) == 0) {
            //System.out.println("Skipping " + Utility.hex(UTF16.valueOf(source, i)));
            continue;
        }

        subpermute.removeAll();

        // see what the permutations of the characters before and after this one are
        //Hashtable *subpermute = permute(source.substring(0,i) + source.substring(i + UTF16.getCharCount(cp)));
        permute(subPermuteString.replace(i, U16_LENGTH(cp), NULL, 0), skipZeros, &subpermute, status);
        /* Test for buffer overflows */
        if(U_FAILURE(status)) {
            return;
        }
        // The upper replace is destructive. The question is do we have to make a copy, or we don't care about the contents 
        // of source at this point.

        // prefix this character to all of them
        ne = subpermute.nextElement(el);
        while (ne != NULL) {
            UnicodeString *permRes = (UnicodeString *)(ne->value.pointer);
            UnicodeString *chStr = new UnicodeString(cp);
            //test for  NULL
            if (chStr == NULL) {
                status = U_MEMORY_ALLOCATION_ERROR;
                return;
            }
            chStr->append(*permRes); //*((UnicodeString *)(ne->value.pointer));
            //if (PROGRESS) printf("  Piece: %s\n", UToS(*chStr));
            result->put(*chStr, chStr, status);
            ne = subpermute.nextElement(el);
        }
    }
    //return result;
}