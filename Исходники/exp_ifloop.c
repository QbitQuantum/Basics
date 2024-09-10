BOOL FASTCALL comProc_IfLoop(U16 flags, S16 *brackCnt)
{
    BOOL        BRACK=FALSE,FAR_BRANCH=FALSE,FLIPOP;
    S32         start,whilestart,offset;
    BANK        *bank;
    U8          *condPtr,*elsePtr;
    int         index,mode;

    CheckCurBank();

    if((mode=StrInStrint(szTemp,siIffys))!=-1) {

        if(mode==IFMODE_DOWHILE) {  
            bank        = curBank;
            start       = GetBankOffset();
            if(STRCMP(GetNextWord(),"while")) {
                // 'ist der code block!
                GetCode(flags|CF_BRACEOK, brackCnt);
                if(STRCMP(GetNextWord(),"while"))
                    error(ERR_WHILEEXP,szTemp);
            }
        }

        if(GetNextWord()[0]!='(')
            error(ERR_INVCOND,szTemp);
        else {
            GetNextWord();
            BRACK = TRUE;
        }

        USE_DEFS        = FALSE;
        if(!STRCMP(szTemp,"far")) {
            FAR_BRANCH = TRUE;
            GetNextWord();
        } else if(!STRCMP(szTemp,"near")) {
            GetNextWord();
        }

        // parse the "is" "is not" "not" "no", etc.
        FLIPOP = FALSE;
        while((index=StrInStrint(szTemp,siIsNot))!=-1) {
            if(!siIsNot[index].index)
                FLIPOP = !FLIPOP;
            GetNextWord();
        }
                            
        USE_DEFS        = TRUE;
        if(!PRECOMPILING) {   
            if((index=StrInStrint(szTemp,siConditions))==-1) {
                error(ERR_INVALIDCOND,szTemp);
                condPtr = NULL;
            } else {
                if(mode==IFMODE_IF || mode==IFMODE_WHILE)
                    FLIPOP = !FLIPOP;
                index = (FLIPOP)?
                    RelSwapOp(siConditions[index].index):
                    siConditions[index].index;

                if(mode==IFMODE_WHILE)
                    whilestart = GetBankOffset();

                if(FAR_BRANCH) {
                    WriteOpcodeB(RelSwapOp(index),3);
                    WriteOpcode(opJMP_ABS);
                    condPtr = curBank->ptr;
                    WriteCodeW(0);
                } else {
                    condPtr = curBank->ptr+1;
                    WriteOpcodeB(index,0);
                }
            }    
            if(mode!=IFMODE_DOWHILE) {
                bank    = curBank;
                start   = GetBankOffset();
            }
        }
                         
        if(BRACK && GetNextWord()[0]!=')') {
            error(ERR_IFCONDCLOSEEXP,szTemp);
        }
          
        if(mode!=IFMODE_DOWHILE)
            GetCode(flags|CF_BRACEOK|CF_GETNEXTWORD, brackCnt);

        elsePtr = NULL;
        if(!STRCMP(PeekNextWord(),"else")) {
            GetNextWord();
            if(mode!=IFMODE_IF)
                error(ERR_ONLYIFSELSE);
            else {         
                if(!PRECOMPILING)
                    WriteOpcode(opJMP_ABS);
                elsePtr = curBank->ptr;
                if(!PRECOMPILING)
                    WriteCodeW(0);
            }
        }

        if(!PRECOMPILING) {
            if(bank     != curBank)
                error(ERR_FOREVEROUTOFBANK,bank->label,curBank->label);
            else if(condPtr) {
                if(mode==IFMODE_WHILE) {
                    WriteOpcodeW(opJMP_ABS,whilestart);
                }
                if(FAR_BRANCH) {  
                    if(mode==IFMODE_DOWHILE) {
                        PUTW(condPtr,start);
                    } else {
                        PUTW(condPtr,GetBankOffset());
                    }
                } else {
                    offset = mode==IFMODE_DOWHILE?
                        start-GetBankOffset():
                        GetBankOffset()-start;

                    if((offset<-128 || offset>127))
                        error(ERR_BRANCHOUTOFRANGE);
                    else
                        PUTB(condPtr,(U8)offset);
                }
            }
        }
        if(elsePtr) {
            GetCode(flags|CF_BRACEOK|CF_GETNEXTWORD, brackCnt);
            if(!PRECOMPILING)
                PUTW(elsePtr,GetBankOffset());
        }

    } else if(!STRCMP(szTemp,"forever")) {

        bank    = curBank;
        start   = GetBankOffset();

        GetCode(flags|CF_BRACEOK|CF_GETNEXTWORD, brackCnt);

        if(bank != curBank)
            error(ERR_FOREVEROUTOFBANK,bank->label,curBank->label);
        else
            WriteOpcodeW(opJMP_ABS,start);

    } else
        return FALSE;
    return TRUE;
}