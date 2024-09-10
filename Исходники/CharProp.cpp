StrLen CutLine(StrLen &text)
 {
  for(StrLen next=text; +next ;++next)
    {
     char ch=*next;
     
     if( ch=='\r' || ch=='\n' )
       {
        StrLen ret=text.prefix(next);
        
        ++next;
        
        if( ch=='\r' && +next && *next=='\n' ) ++next;
        
        text=next;
        
        return ret;
       }
    }
  
  return Replace_null(text);
 }