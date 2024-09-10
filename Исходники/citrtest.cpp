void CharIterTest::TestConstructionAndEqualityUChariter() {
    U_STRING_DECL(testText, "Now is the time for all good men to come to the aid of their country.", 69);
    U_STRING_DECL(testText2, "Don't bother using this string.", 31);

    U_STRING_INIT(testText, "Now is the time for all good men to come to the aid of their country.", 69);
    U_STRING_INIT(testText2, "Don't bother using this string.", 31);

    UnicodeString result, result4, result5;

    UCharCharacterIterator* test1 = new UCharCharacterIterator(testText, u_strlen(testText));
    UCharCharacterIterator* test2 = new UCharCharacterIterator(testText, u_strlen(testText), 5);
    UCharCharacterIterator* test3 = new UCharCharacterIterator(testText, u_strlen(testText), 2, 20, 5);
    UCharCharacterIterator* test4 = new UCharCharacterIterator(testText2, u_strlen(testText2));
    UCharCharacterIterator* test5 = (UCharCharacterIterator*)test1->clone();
    UCharCharacterIterator* test6 = new UCharCharacterIterator(*test1);

    // j785: length=-1 will use u_strlen()
    UCharCharacterIterator* test7a = new UCharCharacterIterator(testText, -1);
    UCharCharacterIterator* test7b = new UCharCharacterIterator(testText, -1);
    UCharCharacterIterator* test7c = new UCharCharacterIterator(testText, -1, 2, 20, 5);

    // Bad parameters.
    UCharCharacterIterator* test8a = new UCharCharacterIterator(testText, -1, -1, 20, 5);
    UCharCharacterIterator* test8b = new UCharCharacterIterator(testText, -1, 2, 100, 5);
    UCharCharacterIterator* test8c = new UCharCharacterIterator(testText, -1, 2, 20, 100);

    if (test8a->startIndex() < 0)
        errln("Construction failed: startIndex is negative");
    if (test8b->endIndex() != u_strlen(testText))
        errln("Construction failed: endIndex is different from the text length");
    if (test8c->getIndex() < test8c->startIndex() || test8c->endIndex() < test8c->getIndex())
        errln("Construction failed: index is invalid");

    if (*test1 == *test2 || *test1 == *test3 || *test1 == *test4 )
        errln("Construction or operator== failed: Unequal objects compared equal");
    if (*test1 != *test5 )
        errln("clone() or equals() failed: Two clones tested unequal");

    if (*test6 != *test1 )
        errln("copy construction or equals() failed: Two copies tested unequal");

    if (test1->hashCode() == test2->hashCode() || test1->hashCode() == test3->hashCode()
                    || test1->hashCode() == test4->hashCode())
        errln("hashCode() failed:  different objects have same hash code");

    if (test1->hashCode() != test5->hashCode())
        errln("hashCode() failed:  identical objects have different hash codes");
     
    test7a->getText(result);
    test7b->getText(result4);
    test7c->getText(result5);

    if(result != UnicodeString(testText) || result4 != result || result5 != result)
        errln("error in construction");
    
    test1->getText(result);
    test4->getText(result4);
    test5->getText(result5); 
    if(result != result5 || result == result4)
        errln("getText() failed");
    test5->setText(testText2, u_strlen(testText2));
    test5->getText(result5);
    if(result == result5 || result4 != result5)
        errln("setText() or getText() failed");
    test5->setText(testText, u_strlen(testText));
    test5->getText(result5);
    if(result != result5 || result == result4)
        errln("setText() or getText() round-trip failed"); 


    test1->setIndex(5);
    if (*test1 != *test2 || *test1 == *test5)
        errln("setIndex() failed");
    test8b->setIndex32(5);
    if (test8b->getIndex()!=5)
        errln("setIndex32() failed");

    *test1 = *test3;
    if (*test1 != *test3 || *test1 == *test5)
        errln("operator= failed");

    delete test1;
    delete test2;
    delete test3;
    delete test4;
    delete test5;
    delete test6;
    delete test7a;
    delete test7b;
    delete test7c;
    delete test8a;
    delete test8b;
    delete test8c;
}