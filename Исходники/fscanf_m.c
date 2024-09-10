errno_t vfscanf_m(FILE *file, const string_m format, int *count, va_list args){
  int orientation;
  errno_t rv;

  if(!format){
    ErrorHandler("vfscanf_m: 2nd Argument NULL Pointer", format, EINVAL);
    ERROR(EINVAL);
  }

  orientation = fwide(file, 0);

  if(orientation > 0)
    rv = wvfscanf_m(file, format, count, args);
  else 
    rv = cvfscanf_m(file, format, count, args);
  if (rv) ERROR(rv);
  return rv;
}