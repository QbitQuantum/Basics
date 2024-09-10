void   RegexPattern::dumpOp(int32_t index) const {
    static const char * const opNames[] = {URX_OPCODE_NAMES};
    int32_t op          = fCompiledPat->elementAti(index);
    int32_t val         = URX_VAL(op);
    int32_t type        = URX_TYPE(op);
    int32_t pinnedType  = type;
    if ((uint32_t)pinnedType >= sizeof(opNames)/sizeof(char *)) {
        pinnedType = 0;
    }

    REGEX_DUMP_DEBUG_PRINTF(("%4d   %08x    %-15s  ", index, op, opNames[pinnedType]));
    switch (type) {
    case URX_NOP:
    case URX_DOTANY:
    case URX_DOTANY_ALL:
    case URX_FAIL:
    case URX_CARET:
    case URX_DOLLAR:
    case URX_BACKSLASH_G:
    case URX_BACKSLASH_X:
    case URX_END:
    case URX_DOLLAR_M:
    case URX_CARET_M:
        // Types with no operand field of interest.
        break;

    case URX_RESERVED_OP:
    case URX_START_CAPTURE:
    case URX_END_CAPTURE:
    case URX_STATE_SAVE:
    case URX_JMP:
    case URX_JMP_SAV:
    case URX_JMP_SAV_X:
    case URX_BACKSLASH_B:
    case URX_BACKSLASH_BU:
    case URX_BACKSLASH_D:
    case URX_BACKSLASH_Z:
    case URX_STRING_LEN:
    case URX_CTR_INIT:
    case URX_CTR_INIT_NG:
    case URX_CTR_LOOP:
    case URX_CTR_LOOP_NG:
    case URX_RELOC_OPRND:
    case URX_STO_SP:
    case URX_LD_SP:
    case URX_BACKREF:
    case URX_STO_INP_LOC:
    case URX_JMPX:
    case URX_LA_START:
    case URX_LA_END:
    case URX_BACKREF_I:
    case URX_LB_START:
    case URX_LB_CONT:
    case URX_LB_END:
    case URX_LBN_CONT:
    case URX_LBN_END:
    case URX_LOOP_C:
    case URX_LOOP_DOT_I:
        // types with an integer operand field.
        REGEX_DUMP_DEBUG_PRINTF(("%d", val));
        break;

    case URX_ONECHAR:
    case URX_ONECHAR_I:
        REGEX_DUMP_DEBUG_PRINTF(("%c", val<256?val:'?'));
        break;

    case URX_STRING:
    case URX_STRING_I:
        {
            int32_t lengthOp       = fCompiledPat->elementAti(index+1);
            U_ASSERT(URX_TYPE(lengthOp) == URX_STRING_LEN);
            int32_t length = URX_VAL(lengthOp);
            int32_t i;
            for (i=val; i<val+length; i++) {
                UChar c = fLiteralText[i];
                if (c < 32 || c >= 256) {c = '.';}
                REGEX_DUMP_DEBUG_PRINTF(("%c", c));
            }
        }
        break;

    case URX_SETREF:
    case URX_LOOP_SR_I:
        {
            UnicodeString s;
            UnicodeSet *set = (UnicodeSet *)fSets->elementAt(val);
            set->toPattern(s, TRUE);
            for (int32_t i=0; i<s.length(); i++) {
                REGEX_DUMP_DEBUG_PRINTF(("%c", s.charAt(i)));
            }
        }
        break;

    case URX_STATIC_SETREF:
    case URX_STAT_SETREF_N:
        {
            UnicodeString s;
            if (val & URX_NEG_SET) {
                REGEX_DUMP_DEBUG_PRINTF(("NOT "));
                val &= ~URX_NEG_SET;
            }
            UnicodeSet *set = fStaticSets[val];
            set->toPattern(s, TRUE);
            for (int32_t i=0; i<s.length(); i++) {
                REGEX_DUMP_DEBUG_PRINTF(("%c", s.charAt(i)));
            }
        }
        break;


    default:
        REGEX_DUMP_DEBUG_PRINTF(("??????"));
        break;
    }
    REGEX_DUMP_DEBUG_PRINTF(("\n"));
}