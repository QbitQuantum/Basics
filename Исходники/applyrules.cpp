// return values:
// 0: failure
// 1: success, caller must add lemma to the end of the result string
// 2: success, caller must add lemma to the start of the result string
// 3: success, caller must not add lemma to the result string
static int lemmatiseer(const char * word,const char * wordend,const char * buf,const char * maxpos
#if TESTING
                        ,char * start = NULL ,char * middle = NULL ,char * end = NULL
#endif
                        )
    {
    int pos = 0;
    do // loop until matching pattern found
        {
        assert(pos >= 0);
        assert(maxpos == buf+pos || *(int*)(buf+pos) >= 0);
        buf += pos;
        if(buf == maxpos)
            {
            pos = 0;
            return 0;
            }
        else
            pos = *(int*)buf; // pos now points to the next record, which has to be tried if the current record fails.
        const char * p = buf + sizeof(int);
#if TESTING
        int slen = strlen(start);
        int mlen = strlen(middle);
        int elen = strlen(end);
#endif
        switch(*p)
            {
            case 1: // on success, subtree makes lhs of alternating pair
            case 2: // on success, subtree makes rhs of alternating pair
                {
                if(oneAnswer)
                    {
                    if(*p == 1)
                        {
                        p += sizeof(int);
                        int hs = lemmatiseer(word,wordend,p,maxpos
#if TESTING
                            ,start,middle,end
#endif
                            );
#if TESTING
                        start[slen] = 0;
                        middle[mlen] = 0;
                        end[elen] = 0;
#endif
                        return hs ? 3 : 0;
                        }
                    else
                        return 0;
                    }
                p += sizeof(int);
                int hs = lemmatiseer(word,wordend,p,maxpos
#if TESTING
                                    ,start,middle,end
#endif
                                    );
#if TESTING
                start[slen] = 0;
                middle[mlen] = 0;
                end[elen] = 0;
#endif
                return hs ? *p : 0;
                }
            case 3: // on success, subtree makes both lhs and rhs of alternating pair
                {
                p += sizeof(int);
                int altpos = *(int *)p;
                int lhs = lemmatiseer(word,wordend,p + sizeof(int),p + altpos
#if TESTING
                                      ,start,middle,end
#endif
                                      );
                if(oneAnswer)
                    return lhs;
                else
                    {
#if TESTING
                    start[slen] = 0;
                    middle[mlen] = 0;
                    Strrev(end);
                    end[elen] = 0;
                    Strrev(end);
#endif
                    int rhs = lemmatiseer(word,wordend,p + altpos,maxpos
#if TESTING
                                     ,start,middle,end
#endif
                                     );
                    // Not sure whether following test is right.
                    // Is it possible that lhs and rhs both are > 0 but different?
                    //assert(lhs == rhs);
                    // it is possible that eg. lhs fails and rhs succeeds
                    if(lhs)
                        {
                        if(rhs)
                            return 3;
                        else
                            return 1;
                        }
                    else if(rhs)
                        return 2;
                    else
                        return 0;
                    }
                }
            default:
                {
                var vars[20];
                const char * fields[44]; // 44 = (2*20 + 3) + 1
                // The even numbered fields contain patterns
                // The odd numbered fields contain replacements
                // The first two fields (0,1) refer to the prefix
                // The third and fourth (2,3) fields refer to the affix
                // The remaining fields (4,5,..,..) refer to infixes, from left to right
                // output=fields[1]+vars[0]+fields[5]+vars[1]+fields[7]+vars[2]+...+fields[2*n+3]+vars[n]+...+fields[3]
                const char * wend = wordend;
                fields[0] = p;
                int findex = 1;
                while(*p != '\n')
                    {
                //    putchar(*p);
                    if(*p == '\t')
                        fields[findex++] = ++p;
                    else
                        ++p;
                    }
                //putchar('\n');
                fields[findex] = ++p; 
                // fields[findex] points to character after \n. 
                // When 1 is subtracted, it points to the character following the last replacement.
                // p is now within 3 bytes from the first Record of the subtree
                //        printpat(fields,findex);
                // check Lpat
                vars[0].s = samestart(fields,word,wend);
                if(vars[0].s)
                    {
                    // Lpat succeeded
                    vars[0].e = wend;
                    char * destination = NULL;
                    int printed = 0;
                    int subres = 0;
                    if(findex > 2) // there is more than just a prefix
                        {
                        const char * newend = sameend(fields,vars[0].s,wend);
                        if(newend)
                            wend = newend;
                        else
                            continue; //suffix didn't match

                        int k;
                        const char * w = vars[0].s;
                        int vindex = 0;
                        for(k = 4;k < findex;k += 2)
                            {
                            if(!substr(fields,k,w,wend,vars,vindex))
                                break;
                            ++vindex;
                            w = vars[vindex].s;
                            }
                        if(k < findex)
                            continue;

                        vars[vindex].e = newend;
                        // Find first record of subtree, if there is any
                        long nxt = p - buf;
                        nxt += sizeof(int)-1;
                        nxt /= sizeof(int);
                        nxt *= sizeof(int);
#if TESTING
                        char _end[30];
                        if(start)
                            {
                            printpat2(fields,findex,start+strlen(start),middle,_end);
                            strcpy(_end+strlen(_end),end);
                            strcpy(end,_end);
                            }
#endif
                        const char * mmaxpos = pos ? buf + pos : maxpos;
                        const char * mbuf = buf + nxt;
                        assert(buf <= mmaxpos);
                        if(  mbuf >= mmaxpos                              // There is no subtree
                          || (subres = lemmatiseer(vars[0].s,wend,mbuf,mmaxpos // There is a subtree, but it has no matching records
#if TESTING
                                                  ,start,middle,end
#endif
                                                  )
                             ) < 3 // if subres IS 3, this rule must not fire.
                          )
                            {//                     length of prefix       length of first unmatched         length of suffix
                            int resultlength = (fields[2] - fields[1] - 1) + (vars[0].e - vars[0].s) + (fields[4] - fields[3] - 1);
#if TESTING
                            int replacementlength = (fields[2] - fields[1] - 1) + 1 + (fields[4] - fields[3] - 1);
#endif
                            int m;
                            for(m = 1;2*m+3 < findex;++m)
                                {
                                int M = 2*m+3;
                                //                    length of infix       length of unmatched after infix
                                resultlength += (fields[M+1] - fields[M] - 1) + (vars[m].e - vars[m].s);
#if TESTING
                                replacementlength += (fields[M+1] - fields[M] - 1) + 1;
#endif
                                }
                            destination = new char[resultlength+1];
                            printed = sprintf(destination,"%.*s%.*s",fields[2] - fields[1] - 1,fields[1],vars[0].e - vars[0].s,vars[0].s);
#if TESTING
                            replacement = new char[replacementlength+1];
                            int printed2 = sprintf(replacement,"%.*s%.*s",fields[2] - fields[1] - 1,fields[1],1,"*");
#endif
                            for(m = 1;2*m+3 < findex;++m)
                                {
                                int M = 2*m+3;
                                printed += sprintf(destination+printed,"%.*s%.*s",fields[M+1] - fields[M] - 1,fields[M],vars[m].e - vars[m].s,vars[m].s);
#if TESTING
                                printed2 += sprintf(replacement+printed2,"%.*s%.*s",fields[M+1] - fields[M] - 1,fields[M],1,"*");
#endif
                                }
                            printed += sprintf(destination+printed,"%.*s",fields[4] - fields[3] - 1,fields[3]);
#if TESTING
                            sprintf(replacement+printed2,"%.*s",fields[4] - fields[3] - 1,fields[3]);
#endif
                            }
                        }
                    else if(vars[0].e == vars[0].s) // whole-word match: everything matched by "prefix"
                        {
                        subres = 0;
                        destination = new char[(fields[2] - fields[1] - 1)+1];
                        printed = sprintf(destination,"%.*s",fields[2] - fields[1] - 1,fields[1]);
#if TESTING
                        replacement = new char[(fields[2] - fields[1] - 1)+1];
                        sprintf(replacement,"%.*s",fields[2] - fields[1] - 1,fields[1]);
                        char _end[30];
                        if(start)
                            {
                            printpat2(fields,findex,start+strlen(start),middle,_end);
                            strcpy(_end+strlen(_end),end);
                            strcpy(end,_end);

                            }
#endif
                        }
                    else
                        continue; // something unmatched

                    if(destination)
                        {
#if TESTING
                        char temp[1000];
                        if(findex == 2)
                            sprintf(temp,"%s:%s%s%s->%s %d",destination,start,middle,end,replacement,findex);
                        else
                            sprintf(temp,"%s:%s%s*%s->%s %d",destination,start,middle,end,replacement,findex);
                        printf("%s\n",temp);
#endif
                        assert(subres < 3);
                        if(!result)
                            {
                            assert(subres == 0);
                            result = destination;
                            }
                        else // Check whether an alternative lemma was found
                            {
                            //assert(subres == 1 || subres == 2);
                            char * sub = strstr(result,destination);
                            if(  !sub 
                              || (  sub != result 
                                 && sub[-1] != ' '
                                 ) 
                              || (  sub[printed] != '\0'
                                 && sub[printed] != ' '
                                 )
                              )
                                { // Yes, lemma was not found already
                                char * newresult = new char[strlen(result)+printed+2];
                                if(subres == 1)
                                    sprintf(newresult,"%s %s",result,destination);
                                else if(subres == 2)
                                    sprintf(newresult,"%s %s",destination,result);
                                else
                                    sprintf(newresult,"%s %s",result,destination);
                                delete [] result;
                                result = newresult;
                                }
                            delete [] destination;
                            }
                        }
                    return 3;
                    }
                else
                    {
                    // Lpat failed
                    continue; // prefix failed
                    }
                }
            }
        }
    while(pos);
    return 0;
    }