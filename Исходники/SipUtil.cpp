 /*
  * trim a string left & right space
  * buf = "  expires = 3000; " return "expires = 3000;"
  */
string TrimString(CStrRef buf)
{
    LPCSTR p = buf.c_str();
    LPCSTR q = p + buf.length();
    
    for(; isspace(*p) && p <= q;) ++ p;

    for(; (*q == '\0' || isspace(*q)) && p <= q;) -- q;
    ++ q;
    
    string res;
    if(p < q) 
        res.assign(p, q);
    
    return res;
}