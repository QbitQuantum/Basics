char* LOSyncSource::getNewCard(bool isAdd) {
    
    int suffix = (isAdd ? count : count+2);
    StringBuffer filetest;
    if (useSif) {
        filetest.sprintf("sif%i.txt", suffix);
    } else {
        filetest.sprintf("vcard%i.txt", suffix);
    }
    char* card = loadTestFile("LOItemTest", filetest.c_str(), true);
    count++;    
    return card;

}