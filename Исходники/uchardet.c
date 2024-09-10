/*
 * call-seq:
 *   input_filtered=
 *
 * Enable filtering of input text. If filtering is enabled,
 * text within angle brackets ("<" and ">") will be removed
 * before detection, which will remove most HTML or xml markup.
 */
static VALUE
UCharsetDetector_set_input_filtered(VALUE self, VALUE flag)
{
    UCharsetDetector *detector;
    Data_Get_Struct(self, UCharsetDetector, detector);
    
    ucsdet_enableInputFilter(detector, RTEST(flag) ? TRUE : FALSE);
    return self;
}