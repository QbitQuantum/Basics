 const mat2& invert(bool *invertible=NULL)
 {
     *this = inverse(invertible);
     return *this;
 }