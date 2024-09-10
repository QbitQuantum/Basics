static char *parse_signature_file(file_stat_t *file_stat, char *pos)
{
  while(*pos!='\0')
  {
    /* skip comments */
    while(*pos=='#')
    {
      while(*pos!='\0' && *pos!='\n')
	pos++;
      if(*pos=='\0')
	return pos;
      pos++;
    }
    /* each line is composed of "extension offset signature" */
    {
      char *extension;
      unsigned int offset=0;
      unsigned char *tmp=NULL;
      unsigned int signature_max_size=512;
      unsigned int signature_size=0;
      {
	const char *extension_start=pos;
	while(*pos!='\0' && !isspace(*pos))
	  pos++;
	if(*pos=='\0')
	  return pos;
	*pos='\0';
	extension=strdup(extension_start);
	pos++;
      }
      /* skip space */
      while(isspace(*pos))
	pos++;
      /* read offset */
      pos=str_uint(pos, &offset);
      /* read signature */
      tmp=(unsigned char *)MALLOC(signature_max_size);
      while(*pos!='\n' && *pos!='\0')
      {
	if(signature_size==signature_max_size)
	{
	  unsigned char *tmp_old=tmp;
	  signature_max_size*=2;
	  tmp=(unsigned char *)realloc(tmp, signature_max_size);
	  if(tmp==NULL)
	  {
	    free(extension);
	    free(tmp_old);
	    return pos;
	  }
	}
	if(isspace(*pos) || *pos=='\r' || *pos==',')
	  pos++;
	else if(*pos== '\'')
	{
	  pos++;
	  if(*pos=='\0')
	  {
	    free(extension);
	    free(tmp);
	    return pos;
	  }
	  else if(*pos=='\\')
	  {
	    pos++;
	    if(*pos=='\0')
	    {
	      free(extension);
	    free(tmp);
	      return pos;
	    }
	    else if(*pos=='b')
	      tmp[signature_size++]='\b';
	    else if(*pos=='n')
	      tmp[signature_size++]='\n';
	    else if(*pos=='t')
	      tmp[signature_size++]='\t';
	    else if(*pos=='r')
	      tmp[signature_size++]='\r';
	    else if(*pos=='0')
	      tmp[signature_size++]='\0';
	    else
	      tmp[signature_size++]=*pos;
	    pos++;
	  }
	  else
	  {
	    tmp[signature_size++]=*pos;
	    pos++;
	  }
	  if(*pos!='\'')
	  {
	    free(extension);
	    free(tmp);
	    return pos;
	  }
	  pos++;
	}
	else if(*pos=='"')
	{
	  pos++;
	  for(; *pos!='"' && *pos!='\0'; pos++)
	  {
	    if(signature_size==signature_max_size)
	    {
	      unsigned char *tmp_old=tmp;
	      signature_max_size*=2;
	      tmp=(unsigned char *)realloc(tmp, signature_max_size);
	      if(tmp==NULL)
	      {
		free(extension);
		free(tmp_old);
		return pos;
	      }
	    }
	    if(*pos=='\\')
	    {
	      pos++;
	      if(*pos=='\0')
	      {
		free(extension);
		free(tmp);
		return pos;
	      }
	      else if(*pos=='b')
		tmp[signature_size++]='\b';
	      else if(*pos=='n')
		tmp[signature_size++]='\n';
	      else if(*pos=='r')
		tmp[signature_size++]='\r';
	      else if(*pos=='t')
		tmp[signature_size++]='\t';
	      else if(*pos=='0')
		tmp[signature_size++]='\0';
	      else
		tmp[signature_size++]=*pos;
	    }
	    else
	      tmp[signature_size++]=*pos;;
	  }
	  if(*pos!='"')
	  {
	    free(extension);
	    free(tmp);
	    return pos;
	  }
	  pos++;
	}
	else if(*pos=='0' && (*(pos+1)=='x' || *(pos+1)=='X'))
	{
	  pos+=2;
	  while(isxdigit(*pos) && isxdigit(*(pos+1)))
	  {
	    unsigned int val=(*pos);
	    if(*pos>='0' && *pos<='9')
	      val-='0';
	    else if(*pos>='A' && *pos<='F')
	      val=val-'A'+10;
	    else if(*pos>='a' && *pos<='f')
	      val=val-'a'+10;
	    pos++;
	    val*=16;
	    val+=(*pos);
	    if(*pos>='0' && *pos<='9')
	      val-='0';
	    else if(*pos>='A' && *pos<='F')
	      val=val-'A'+10;
	    else if(*pos>='a' && *pos<='f')
	      val=val-'a'+10;
	    pos++;
	    tmp[signature_size++]=val;
	  }
	}
	else
	{
	  free(extension);
	  free(tmp);
	  return pos;
	}
      }
      if(*pos=='\n')
	pos++;
      if(signature_size>0)
      {
	/* FIXME: Small memory leak */
	unsigned char *signature=(unsigned char *)MALLOC(signature_size);
	log_info("register a signature for %s\n", extension);
	memcpy(signature, tmp, signature_size);
	register_header_check(offset, signature, signature_size, &header_check_sig, file_stat);
	signature_insert(extension, offset, signature, signature_size);
      }
      else
      {
	free(extension);
      }
      free(tmp);
    }
  }
  return pos;
}