int pmatch_quot(char **P_PtrPtr, char **S_PtrPtr, int *Flags)
{
    int result=MATCH_FAIL, OldFlags;
    char P_Char, S_Char, *OldPos;

    P_Char=**P_PtrPtr;
    S_Char=**S_PtrPtr;

    switch (P_Char)
    {
    case 'b':
        if (S_Char=='\b') result=MATCH_ONE;
        break;
    case 'e':
        if (S_Char==27) result=MATCH_ONE;
        break; //escape
    case 'n':
        if (S_Char=='\n') result=MATCH_ONE;
        break;
    case 'r':
        if (S_Char=='\r') result=MATCH_ONE;
        break;
    case 't':
        if (S_Char=='	') result=MATCH_ONE;
        break;
    case 'l':
        if (islower(S_Char)) result=MATCH_ONE;
        break;
    case 'x':
        result=MATCH_HEX;
        break;
    case 'A':
        if (isalpha(S_Char)) result=MATCH_ONE;
        break;
    case 'B':
        if (isalnum(S_Char)) result=MATCH_ONE;
        break;
    case 'D':
        if (isdigit(S_Char)) result=MATCH_ONE;
        break;
    case 'S':
        if (isspace(S_Char)) result=MATCH_ONE;
        break;
    case 'P':
        if (ispunct(S_Char)) result=MATCH_ONE;
        break;
    case 'X':
        if (isxdigit(S_Char)) result=MATCH_ONE;
        break;
    case 'U':
        if (isupper(S_Char)) result=MATCH_ONE;
        break;
    case '+':
        result=MATCH_SWITCH_ON;
        break;
    case '-':
        result=MATCH_SWITCH_OFF;
        break;

    default:
        if (S_Char==P_Char) result=MATCH_ONE;
        break;
    }

    switch (result)
    {
    case MATCH_ONE:
        (*P_PtrPtr)++;
        break;

    case MATCH_HEX:
        if (! pmatch_ascii((*P_PtrPtr)+1,S_Char,MATCH_HEX)) return(MATCH_FAIL);
        (*P_PtrPtr)+=2;
        break;

    case MATCH_OCTAL:
        if (! pmatch_ascii((*P_PtrPtr)+1,S_Char,MATCH_OCTAL)) return(MATCH_FAIL);
        (*P_PtrPtr)+=3;
        break;

    case MATCH_SWITCH_ON:
    case MATCH_SWITCH_OFF:


        //some switches need to be applied in order for a pattern to match
        //(like the case-insensitive switch) others should only be applied if
        //it matches. So we apply the switch, but if the subsequent pmatch_char fails
        //we unapply it
        OldFlags=*Flags;
        OldPos=*P_PtrPtr;
        (*P_PtrPtr)++; //go past the + or - to the actual type
        pmatch_switch(**P_PtrPtr, result, Flags);
        (*P_PtrPtr)++;
        result=pmatch_char(P_PtrPtr, S_PtrPtr, Flags);

        if ((result==MATCH_FAIL) || (result==MATCH_CONT))
        {
            *P_PtrPtr=OldPos;
            *Flags=OldFlags;
        }
        return(result);
        break;

    case MATCH_FAIL:
        if (*Flags & PMATCH_SUBSTR) return(MATCH_CONT);
        return(MATCH_FAIL);
        break;
    }

    return(MATCH_ONE);
}