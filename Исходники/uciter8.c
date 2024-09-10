static void
TestLenient8Iterator() {
    static const UChar text[]={
        0x61, 0x62, 0x63,
        /* dffd 107fd             d801    dffd - in UTF-16, U+107fd=<d801 dffd> */
        0xdffd, 0xd801, 0xdffd, 0xd801, 0xdffd, 
        0x78, 0x79, 0x7a, 0
    };
    static const uint8_t bytes[]={
        0x61, 0x62, 0x63,
        /* dffd            107fd                    d801               dffd - mixture */
        0xed, 0xbf, 0xbd,  0xf0, 0x90, 0x9f, 0xbd,  0xed, 0xa0, 0x81,  0xed, 0xbf, 0xbd,
        0x78, 0x79, 0x7a, 0
    };

    UCharIterator iter1, iter2;
    UChar32 c1, c2;
    int32_t length;

    puts("test a UCharIterator for lenient 8-bit Unicode (accept single surrogates)");

    /* compare the same string between UTF-16 and lenient-8 UCharIterators */
    uiter_setString(&iter1, text, -1);
    uiter_setLenient8(&iter2, (const char *)bytes, sizeof(bytes)-1);
    compareIterators(&iter1, "UTF16Iterator", &iter2, "Lenient8Iterator");

    /* try again with length=-1 */
    uiter_setLenient8(&iter2, (const char *)bytes, -1);
    compareIterators(&iter1, "UTF16Iterator", &iter2, "Lenient8Iterator_1");

    /* test get/set state */
    length=LENGTHOF(text)-1;
    uiter_setLenient8(&iter1, bytes, -1);
    testIteratorState(&iter1, &iter2, "Lenient8IteratorState", length/2);
    testIteratorState(&iter1, &iter2, "Lenient8IteratorStatePlus1", length/2+1);

    /* ---------------------------------------------------------------------- */

    puts("no output so far means that the lenient-8 iterator works fine");

    puts("iterate forward:\nUTF-16\tlenient-8");
    uiter_setString(&iter1, text, -1);
    iter1.move(&iter1, 0, UITER_START);
    iter2.move(&iter2, 0, UITER_START);
    for(;;) {
        c1=iter1.next(&iter1);
        c2=iter2.next(&iter2);
        if(c1<0 && c2<0) {
            break;
        }
        if(c1<0) {
            printf("\t%04x\n", c2);
        } else if(c2<0) {
            printf("%04x\n", c1);
        } else {
            printf("%04x\t%04x\n", c1, c2);
        }
    }
}