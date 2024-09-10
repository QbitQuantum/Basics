//constructor
NamePrepTransform::NamePrepTransform(UParseError& parseError, UErrorCode& status)
: unassigned(), prohibited(), labelSeparatorSet(){
        
    mapping = NULL;
    bundle = NULL;


    const char* testDataName = IntlTest::loadTestData(status);
    
    if(U_FAILURE(status)){
        return;
    }
    
    bundle = ures_openDirect(testDataName,"idna_rules",&status);
    
    if(bundle != NULL && U_SUCCESS(status)){
        // create the mapping transliterator
        int32_t ruleLen = 0;
        const UChar* ruleUChar = ures_getStringByKey(bundle, "MapNFKC",&ruleLen, &status);
        int32_t mapRuleLen = 0;
        const UChar *mapRuleUChar = ures_getStringByKey(bundle, "MapNoNormalization", &mapRuleLen, &status);
        UnicodeString rule(mapRuleUChar, mapRuleLen);
        rule.append(ruleUChar, ruleLen);

        mapping = Transliterator::createFromRules(UnicodeString("NamePrepTransform", ""), rule,
                                                   UTRANS_FORWARD, parseError,status);
        if(U_FAILURE(status)) {
          return;
        }

        //create the unassigned set
        int32_t patternLen =0;
        const UChar* pattern = ures_getStringByKey(bundle,"UnassignedSet",&patternLen, &status);
        unassigned.applyPattern(UnicodeString(pattern, patternLen), status);

        //create prohibited set
        patternLen=0;
        pattern =  ures_getStringByKey(bundle,"ProhibitedSet",&patternLen, &status);
        UnicodeString test(pattern,patternLen);
        prohibited.applyPattern(test,status);
#ifdef NPTRANS_DEBUG
        if(U_FAILURE(status)){
            printf("Construction of Unicode set failed\n");
        }

        if(U_SUCCESS(status)){
            if(prohibited.contains((UChar) 0x644)){
                printf("The string contains 0x644 ... !!\n");
            }
            UnicodeString temp;
            prohibited.toPattern(temp,TRUE);

            for(int32_t i=0;i<temp.length();i++){
                printf("%c", (char)temp.charAt(i));
            }
            printf("\n");
        }
#endif
        
        //create label separator set
        patternLen=0;
        pattern =  ures_getStringByKey(bundle,"LabelSeparatorSet",&patternLen, &status);
        labelSeparatorSet.applyPattern(UnicodeString(pattern,patternLen),status);
    }

    if(U_SUCCESS(status) && 
        (mapping == NULL)
      ){
        status = U_MEMORY_ALLOCATION_ERROR;
        delete mapping;
        ures_close(bundle);
        mapping = NULL;
        bundle = NULL;
    }
        
}