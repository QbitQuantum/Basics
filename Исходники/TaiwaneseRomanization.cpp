RomanizationSyllable RomanizationSyllable::convertToPOJSyllable()
{
    RomanizationSyllable syl = *this;
    syl.clearPreparedTone();
    syl.setCursor(0);
    //			if (_inputType==POJSyllable) return syl;
    
    syl.setInputType(POJSyllable);
    syl.clear();
    
    // begin TL->POJ conversion
    unsigned int size = (unsigned int)_symvec.size();
    unsigned int i;
    
    for (i=0; i<size; i++)
    {
        RomanizationSymbol sym1 = _symvec[i];
        string str1 = sym1.symbol();
        
        // fprintf (stderr, "converting to POJ: %s\n", str1.c_str());
        
        string lowstr1 = sym1.symbolInLowerCase();
        
        // oo -> ou
        if (lowstr1=="oo")
        {
            syl.insertCharacterAtCursor(charAccordingToCaseOf('o', str1[0]), sym1.tone());
            syl.insertCharacterAtCursor(charAccordingToCaseOf('u', str1[1]));
            continue;
        }
        
        
        if (hasNextSymbol(i)) {
            RomanizationSymbol sym2 = _symvec[i+1];
            string str2 = sym2.symbol();
            string lowstr2 = sym2.symbolInLowerCase();
            
            // ou -> oo for POJ but not combined ou
            if (lowstr1=="o" && lowstr2=="u") {
                // detect case
                syl.insertCharacterAtCursor(charAccordingToCaseOf('o', str1[0]), sym1.tone());
                syl.insertCharacterAtCursor(charAccordingToCaseOf('u', str2[0]));
                
                i++;
                continue;
            }
            
            
            // ts -> ch with case detection
            if (lowstr1=="t" && lowstr2=="s") {
                // detect case
                syl.insertCharacterAtCursor(charAccordingToCaseOf('c', str1[0]));
                syl.insertCharacterAtCursor(charAccordingToCaseOf('h', str2[0]));
                
                i++;
                continue;
            }
            
            // ue -> oe
            if (lowstr1=="u" && lowstr2=="e") {
                // detect case
                syl.insertCharacterAtCursor(charAccordingToCaseOf('o', str1[0]), sym1.tone());
                syl.insertCharacterAtCursor(charAccordingToCaseOf('e', str2[0]), sym2.tone());
                
                i++;
                continue;
            }
            
            // ua -> oa
            if (lowstr1=="u" && lowstr2=="a") {
                // detect case
                syl.insertCharacterAtCursor(charAccordingToCaseOf('o', str1[0]), sym1.tone());
                syl.insertCharacterAtCursor(charAccordingToCaseOf('a', str2[0]), sym2.tone());
                
                i++;
                continue;
            }
            
            // ik -> ek (at ending)
            if (lowstr1=="i" && lowstr2=="k" && (i+2)==size) {
                // detect case
                syl.insertCharacterAtCursor(charAccordingToCaseOf('e', str1[0]), sym1.tone());
                syl.insertCharacterAtCursor(charAccordingToCaseOf('k', str2[0]), sym2.tone());
                
                i++;
                continue;
            }
            
            if (hasNextNextSymbol(i) && (i+3)==size) {
                RomanizationSymbol sym3 = _symvec[i+2];
                string str3 = sym3.symbol();
                string lowstr3 = sym3.symbolInLowerCase();
                
                // ing -> eng (must be ending)					
                if (lowstr1=="i" && lowstr2=="n" && lowstr3=="g") {
                    // detect case
                    syl.insertCharacterAtCursor(charAccordingToCaseOf('e', str1[0]), sym1.tone());
                    syl.insertCharacterAtCursor(charAccordingToCaseOf('n', str2[0]), sym2.tone());
                    syl.insertCharacterAtCursor(charAccordingToCaseOf('g', str3[0]), sym3.tone());
                    
                    i+=2;
                    continue;
                }
                
                // ouh -> oh (ending)
                if (lowstr1=="o" && lowstr2=="u" && lowstr3=="h") {
                    // detect case
                    syl.insertCharacterAtCursor(charAccordingToCaseOf('o', str1[0]), sym1.tone());
                    syl.insertCharacterAtCursor(charAccordingToCaseOf('h', str2[0]), sym2.tone());
                    
                    i+=2;
                    continue;
                }
            }			
        }
        
        syl.insertSymbolAtCursor(sym1);
    }			
    
    return syl;
}