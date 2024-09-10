    virtual void run() {
        //sleep(10000);
        int32_t line = 0;

        uint8_t sk1[1024], sk2[1024];
        uint8_t *oldSk = NULL, *newSk = sk1;
        int32_t resLen = 0, oldLen = 0;
        int32_t i = 0;

        for(i = 0; i < noLines; i++) {
            resLen = ucol_getSortKey(coll, lines[i].buff, lines[i].buflen, newSk, 1024);

            int32_t res = 0, cmpres = 0, cmpres2 = 0;

            if(oldSk != NULL) {
                res = strcmp((char *)oldSk, (char *)newSk);
                cmpres = ucol_strcoll(coll, lines[i-1].buff, lines[i-1].buflen, lines[i].buff, lines[i].buflen);
                cmpres2 = ucol_strcoll(coll, lines[i].buff, lines[i].buflen, lines[i-1].buff, lines[i-1].buflen);
                //cmpres = res;
                //cmpres2 = -cmpres;

                if(cmpres != -cmpres2) {
                    error("Compare result not symmetrical on line "+ line);
                    break;
                }

                if(((res&0x80000000) != (cmpres&0x80000000)) || (res == 0 && cmpres != 0) || (res != 0 && cmpres == 0)) {
                    error(UnicodeString("Difference between ucol_strcoll and sortkey compare on line ")+ UnicodeString(line));
                    break;
                }

                if(res > 0) {
                    error(UnicodeString("Line %i is not greater or equal than previous line ")+ UnicodeString(i));
                    break;
                } else if(res == 0) { /* equal */
                    res = u_strcmpCodePointOrder(lines[i-1].buff, lines[i].buff);
                    if (res == 0) {
                        error(UnicodeString("Probable error in test file on line %i (comparing identical strings)")+ UnicodeString(i));
                        break;
                    }
                    /*
                     * UCA 6.0 test files can have lines that compare == if they are
                     * different strings but canonically equivalent.
                    else if (res > 0) {
                        error(UnicodeString("Sortkeys are identical, but code point compare gives >0 on line ")+ UnicodeString(i));
                        break;
                    }
                     */
                }
            }

            oldSk = newSk;
            oldLen = resLen;

            newSk = (newSk == sk1)?sk2:sk1;
        }
    }