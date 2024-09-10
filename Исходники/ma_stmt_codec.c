static void convert_from_float(MYSQL_BIND *r_param, const MYSQL_FIELD *field, float val, int size)
{
  double check_trunc_val= (val > 0) ? floor(val) : -floor(-val);
  char *buf= (char *)r_param->buffer;
  switch (r_param->buffer_type)
  {
    case MYSQL_TYPE_TINY:
      *buf= (r_param->is_unsigned) ? (uint8)val : (int8)val;
      *r_param->error= check_trunc_val != (r_param->is_unsigned ? (double)((uint8)*buf) :
                                          (double)((int8)*buf));
      r_param->buffer_length= 1;
    break;
    case MYSQL_TYPE_SHORT:
    case MYSQL_TYPE_YEAR:
    {
      if (r_param->is_unsigned)
      {
        ushort sval= (ushort)val;
        shortstore(buf, sval);
        *r_param->error= check_trunc_val != (double)sval;
      } else { 
        short sval= (short)val;
        shortstore(buf, sval);
        *r_param->error= check_trunc_val != (double)sval;
      } 
      r_param->buffer_length= 2;
    }
    break; 
    case MYSQL_TYPE_LONG:
    {
      if (r_param->is_unsigned)
      {
        uint32 lval= (uint32)val;
        longstore(buf, lval);
        *r_param->error= (check_trunc_val != (double)lval);
      } else {
        int32 lval= (int32)val;
        longstore(buf, lval);
        *r_param->error= (check_trunc_val != (double)lval);
      }
      r_param->buffer_length= 4;
    }
    break; 
    case MYSQL_TYPE_LONGLONG:
    {
      if (r_param->is_unsigned)
      {
        ulonglong llval= (ulonglong)val;
        longlongstore(buf, llval);
        *r_param->error= (check_trunc_val != (double)llval);
      } else {
        longlong llval= (longlong)val;
        longlongstore(buf, llval);
        *r_param->error= (check_trunc_val != (double)llval);
      }
      r_param->buffer_length= 8;
    }
    break; 
    case MYSQL_TYPE_DOUBLE:
    {
      double dval= (double)val;
      memcpy(buf, &dval, sizeof(double));
      r_param->buffer_length= 8;
    }
    break;
    default:
    {
 #define MAX_DOUBLE_STRING_REP_LENGTH 300
     char buff[MAX_DOUBLE_STRING_REP_LENGTH];
     size_t length;
     char *end;

     length= MIN(MAX_DOUBLE_STRING_REP_LENGTH - 1, r_param->buffer_length);

/*     if (field->decimals >= NOT_FIXED_DEC)
     {
       sprintf(buff, "%-*.*g", (int) length-1, DBL_DIG, val);
       length= strlen(buff);
     }
     else */
     {
#ifdef _WIN32
       _gcvt(val, 6, buff);
#else
       gcvt(val, 6, buff);
#endif
       length= strlen(buff);
     }

     /* remove trailing blanks */
     end= strchr(buff, '\0') - 1;
     while (end > buff && *end == ' ')
       *end--= '\0';

     /* check if ZEROFILL flag is active */
     if (field->flags & ZEROFILL_FLAG)
     {
       /* enough space available ? */
       if (field->length < length || field->length > MAX_DOUBLE_STRING_REP_LENGTH - 1)
         break;
       ma_bmove_upp(buff + field->length, buff + length, length);
       memset((char*) buff, 0, field->length - length);
     }
     convert_froma_string(r_param, buff, strlen(buff));
    }  
    break;
  } 
}