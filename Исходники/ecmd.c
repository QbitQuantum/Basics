int16_t parse_cmd_c6_set(char *cmd, char *output, uint16_t len)
{
  char *buf;
  buf = strrchr (cmd, ' ');
  if (!buf)
    return ECMD_ERR_PARSE_ERROR;

  *(buf ++) = 0;

  struct c6_vario_type varvalue;

  if (!control6_get(cmd, &varvalue))
    return ECMD_ERR_PARSE_ERROR;

  if (varvalue.type == C6_TYPE_int8_t || varvalue.type == C6_TYPE_int16_t) {
    /* signed */
    int16_t nv = strtol (buf, NULL, 0);
    int32_t nlv = strtol (buf, NULL, 0);

    if (varvalue.type == C6_TYPE_int8_t) {
      if (nv < INT8_MIN || nv > INT8_MAX)
        range_error: 
          return ECMD_FINAL(snprintf_P(output, len, PSTR("range error.")));
      else
        varvalue.data.d_int8_t = nv;
    }
    else

	if (varvalue.type == C6_TYPE_int32_t) {
	varvalue.data.d_int32_t = nlv;
	}
     
    else
      varvalue.data.d_int16_t = nv;
      
  }
  else {
    /* unsigned */
    if (*buf == '-') goto range_error;

    uint16_t nv = strtoul (buf, NULL, 0);
    uint32_t nlv = strtoul (buf, NULL, 0);

    if (varvalue.type == C6_TYPE_uint8_t) {
      if (nv > UINT8_MAX)
        goto range_error;
      else
        varvalue.data.d_uint8_t = nv;
    }
    else
    
	if (varvalue.type == C6_TYPE_uint32_t) {
	varvalue.data.d_uint32_t = nlv;
	}
    
    else
      varvalue.data.d_uint16_t = nv;
    }

  control6_set (cmd, varvalue);
  return ECMD_FINAL_OK;
}