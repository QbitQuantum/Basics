 StriWrapLineStart(const String8& s, R_len_t v) :
    str(s.c_str()) {
    nbytes  = s.length()+v;
    count   = s.countCodePoints()+v;
    width   = stri__width_string(s.c_str(), s.length());
    str.append(std::string(v, ' '));
 }