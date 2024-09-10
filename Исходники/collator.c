/**
 * call-seq:
 *     collator.get_attr(attribute)
 *     collator[attribute]
 *
 * Universal attribute setter. See above for valid attributes and their values
 **/
VALUE icu4r_col_get_attr(VALUE self, VALUE obj)
{
    UErrorCode status = U_ZERO_ERROR;
    UColAttributeValue val;
    Check_Type(obj, T_FIXNUM);
    val = ucol_getAttribute(UCOLLATOR(self), FIX2INT(obj), &status);
    ICU_RAISE(status);
    return INT2FIX(val);
}