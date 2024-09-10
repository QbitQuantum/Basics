void DoFixOffs(FIXOFFS *fix)
{
    S32 value,newoffset;

    if(fix) {
        while(fix) {
            value = GetLabelObjectOffset(fix->data, fix->type);
            if(fix->size==FIXOFFS_NEAR) {
                newoffset = (S32)value-fix->org;
                if(newoffset<-128||newoffset>127) {
                    errorf(fix->filename,fix->line,ERR_FIXOFFSNEAR,GetLabelObjectName(fix->data, fix->type));
                } else
                    PUTB(fix->ptr, (U8)newoffset);
            } else if(fix->size==FIXOFFS_FAR) {
                PUTW(fix->ptr, (U16)value);
            } else if(fix->size==FIXOFFS_WORD) {
                PUTW(fix->ptr, (U16)value);
            } else if(fix->size==FIXOFFS_BYTE) {
                PUTB(fix->ptr, (U8)value);
            } else {
                newoffset = AccOpNum(fix->size-FIXOFFS_ARITH, (U16)value);
                PUTB(fix->ptr, (U8)newoffset);
            }
            fix = fix->prev;
        }
    }
}