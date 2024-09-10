   bool operator() (int a, int b) const
   {
//      if (col) {
         UErrorCode status = U_ZERO_ERROR;
         int ret = (int)ucol_strcollUTF8(col,
            cont->get(a).c_str(), cont->get(a).length(),
            cont->get(b).c_str(), cont->get(b).length(), &status);
         STRI__CHECKICUSTATUS_THROW(status, {/* do nothing special on err */})
         return (decreasing)?(ret > 0):(ret < 0);