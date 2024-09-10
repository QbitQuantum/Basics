static le_int32 getCharClass(LEUnicode ch, LEUnicode &lead, LEUnicode &vowel, LEUnicode &trail)
{
    lead  = LJMO_FILL;
    vowel = VJMO_FILL;
    trail = TJMO_FIRST;

    if (ch >= LJMO_FIRST && ch <= LJMO_LAST) {
        lead  = ch;
        return CC_L;
    }

    if (ch >= VJMO_FIRST && ch <= VJMO_LAST) {
        vowel = ch;
        return CC_V;
    }

    if (ch > TJMO_FIRST && ch <= TJMO_LAST) {
        trail = ch;
        return CC_T;
    }

    le_int32 c = decompose(ch, lead, vowel, trail);

    if (c == 2) {
        return CC_LV;
    }

    if (c == 3) {
        return CC_LVT;
    }

    trail = ch;
    return CC_X;
}