static int cs_value(MY_XML_PARSER *st,const char *attr, size_t len)
{
  struct my_cs_file_info *i= (struct my_cs_file_info *)st->user_data;
  const struct my_cs_file_section_st *s;
  int  state= (int)((s= cs_file_sec(st->attr, strlen(st->attr))) ? s->state :
                    0);
  
  switch (state) {
  case _CS_ID:
    i->cs.number= strtol(attr,(char**)NULL,10);
    break;
  case _CS_BINARY_ID:
    i->cs.binary_number= strtol(attr,(char**)NULL,10);
    break;
  case _CS_PRIMARY_ID:
    i->cs.primary_number= strtol(attr,(char**)NULL,10);
    break;
  case _CS_COLNAME:
    i->cs.name=mstr(i->name,attr,len,MY_CS_NAME_SIZE-1);
    break;
  case _CS_CSNAME:
    i->cs.csname=mstr(i->csname,attr,len,MY_CS_NAME_SIZE-1);
    break;
  case _CS_CSDESCRIPT:
    i->cs.comment=mstr(i->comment,attr,len,MY_CS_CSDESCR_SIZE-1);
    break;
  case _CS_FLAG:
    if (!strncmp("primary",attr,len))
      i->cs.state|= MY_CS_PRIMARY;
    else if (!strncmp("binary",attr,len))
      i->cs.state|= MY_CS_BINSORT;
    else if (!strncmp("compiled",attr,len))
      i->cs.state|= MY_CS_COMPILED;
    break;
  case _CS_UPPERMAP:
    fill_uchar(i->to_upper,MY_CS_TO_UPPER_TABLE_SIZE,attr,len);
    i->cs.to_upper=i->to_upper;
    break;
  case _CS_LOWERMAP:
    fill_uchar(i->to_lower,MY_CS_TO_LOWER_TABLE_SIZE,attr,len);
    i->cs.to_lower=i->to_lower;
    break;
  case _CS_UNIMAP:
    fill_uint16(i->tab_to_uni,MY_CS_TO_UNI_TABLE_SIZE,attr,len);
    i->cs.tab_to_uni=i->tab_to_uni;
    break;
  case _CS_COLLMAP:
    fill_uchar(i->sort_order,MY_CS_SORT_ORDER_TABLE_SIZE,attr,len);
    i->cs.sort_order=i->sort_order;
    break;
  case _CS_CTYPEMAP:
    fill_uchar(i->ctype,MY_CS_CTYPE_TABLE_SIZE,attr,len);
    i->cs.ctype=i->ctype;
    break;
  case _CS_RESET:
  case _CS_DIFF1:
  case _CS_DIFF2:
  case _CS_DIFF3:
  case _CS_IDENTICAL:
    {
      /*
        Convert collation description from
        Locale Data Markup Language (LDML)
        into ICU Collation Customization expression.
      */
      char arg[16];
      const char *cmd[]= {"&","<","<<","<<<","="};
      i->cs.tailoring= i->tailoring;
      mstr(arg,attr,len,sizeof(arg)-1);
      if (i->tailoring_length + 20 < sizeof(i->tailoring))
      {
        char *dst= i->tailoring_length + i->tailoring;
        i->tailoring_length+= sprintf(dst," %s %s",cmd[state-_CS_RESET],arg);
      }
    }
  }
  return MY_XML_OK;
}