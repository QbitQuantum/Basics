 UINT64 *Uint64Comp::u_strdup(UINT64 *s) {
     int length = u_strlen(s) + 1;
     UINT64 *result = (UINT64*)malloc(length*sizeof(UINT64));
     if (result == (UINT64*)0){return (UINT64*)0;}
     u_strcpy(result, s);
     return result;
 }