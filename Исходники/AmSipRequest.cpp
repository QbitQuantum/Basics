bool findHeader(const string& hdrs,const string& hdr_name, 
		size_t& pos1, size_t& pos2, size_t& hdr_start)
{
  unsigned int p;
  char* hdr = strdup(hdr_name.c_str());
  const char* hdrs_c = hdrs.c_str();
  char* hdr_c = hdr;
  const char* hdrs_end = hdrs_c + hdrs.length();
  const char* hdr_end = hdr_c + hdr_name.length(); 

  while(hdr_c != hdr_end){
    if('A' <= *hdr_c && *hdr_c <= 'Z')
      *hdr_c -= 'A' - 'a';
    hdr_c++;
  }

  while(hdrs_c != hdrs_end){

    hdr_c = hdr;

    while((hdrs_c != hdrs_end) && (hdr_c != hdr_end)){

      char c = *hdrs_c;
      if('A' <= *hdrs_c && *hdrs_c <= 'Z')
	c -= 'A' - 'a';

      if(c != *hdr_c)
	break;

      hdr_c++;
      hdrs_c++;
    }

    if(hdr_c == hdr_end)
      break;

    while((hdrs_c != hdrs_end) && (*hdrs_c != '\n'))
      hdrs_c++;

    if(hdrs_c != hdrs_end)
      hdrs_c++;
  }
    
  if(hdr_c == hdr_end){
    hdr_start = hdrs_c - hdrs.c_str();;

    while((hdrs_c != hdrs_end) && (*hdrs_c == ' '))
      hdrs_c++;

    if((hdrs_c != hdrs_end) && (*hdrs_c == ':')){

      hdrs_c++;
      while((hdrs_c != hdrs_end) && (*hdrs_c == ' '))
	hdrs_c++;
	    
      p = hdrs_c - hdrs.c_str();
	    
      string::size_type p_end;
      if((p_end = hdrs.find('\n',p)) != string::npos){
		
	free(hdr);
	// return hdrs.substr(p,p_end-p);
	pos1 = p;
	pos2 = p_end;
	return true;
      }
    }
  }

  free(hdr);
  //    return "";
  return false;
}