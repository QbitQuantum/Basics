void TransliteratorAPITest::keyboardAux(Transliterator *t, UnicodeString DATA[], UnicodeString& s, int32_t begin, int32_t end) {
    UTransPosition index={0, 0, 0, 0};
    UErrorCode status=U_ZERO_ERROR;
    for (int32_t i=begin; i<end; i=i+5) {
        UnicodeString log;
        if (DATA[i+0] != "") {
             log = s + " + " + DATA[i] + " -> ";
             index.contextStart=getInt(DATA[i+2]);
             index.contextLimit=index.limit=getInt(DATA[i+3]);
             index.start=getInt(DATA[i+4]);
             t->transliterate(s, index, DATA[i+0], status);
             if(U_FAILURE(status)){
                 errln("FAIL: " + t->getID()+ ".transliterate(Replaceable, int32_t[], UnicodeString, UErrorCode)-->" + (UnicodeString)u_errorName(status));
             continue;
             }
           log = s + " => ";
           t->finishTransliteration(s, index);
        }
         // Show the start index '{' and the cursor '|'
      displayOutput(s, DATA[i+1], log, index);
        
    }
}