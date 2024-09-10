  bool UlamTypeInfoClass::InitFrom(ByteSource & cbs)
  {
    u32 arraylen, bitsize, namelen, parms;
    if (!cbs.Scan(arraylen, Format::LEX32, 0)) return false;
    if (!cbs.Scan(bitsize, Format::LEX32, 0)) return false;
    if (!cbs.Scan(namelen, Format::LEXHD, 0)) return false;

    OStringClassName name;
    for (u32 i = 0; i < namelen; ++i)
    {
      s32 ch = cbs.Read();
      if (ch < 0) return false;
      name.WriteByte((u8) ch);
    }

    if (!cbs.Scan(parms, Format::LEX32, 0)) return false;

    UlamTypeInfoClassParameterArray parameters;
    for (u32 i = 0; i < parms; ++i)
    {
      UlamTypeInfoParameter uticp;
      if (!uticp.m_parameterType.InitFrom(cbs)) return false;

      if (uticp.m_parameterType.m_primType == UlamTypeInfoPrimitive::STRING)
	{
	  u32 strlen;
	  if (cbs.Scanf("%02x",&strlen) != 1) return false;
	  uticp.m_stringValue.Reset();
	  uticp.m_stringValue.WriteByte((u8) strlen); // length into [0]
	  for (u32 j = 0; j < strlen; ++j) {
	    u32 chr;
	    if (cbs.Scanf("%02x",&chr) != 1) return false;
	    uticp.m_stringValue.WriteByte((u8) chr);
	  }
	}
      else if (uticp.m_parameterType.m_primType == UlamTypeInfoPrimitive::CONST_CLASS)
        {
	  u32 hexlen;
	  if (!cbs.Scan(hexlen, Format::LEXHD, 0)) return false;

	  for(u32 j = 0; j < hexlen; j++)
	    {
	      s32 ch = cbs.Read(); //throw away for now..
	      if (ch < 0) return false;
	    }
        }
      else
	{
	  u32 arrayloop = uticp.m_parameterType.m_arrayLength;
	  if(arrayloop > MAX_CLASS_PARAMETER_ARRAY_LENGTH) return false;
	  arrayloop = ((arrayloop == 0) ? 1 : arrayloop);

	  for(u32 j = 0; j < arrayloop; j++)
	    {
	      s32 ch = cbs.Read();
	      if (ch < 0) return false;
	      if (ch != 'n') cbs.Unread();

	      if (!cbs.Scan(uticp.m_value[j], Format::LEX32, 0)) return false;
	      if (ch == 'n') {
		if (uticp.m_value[j] == 0)
		  uticp.m_value[j] = (u32) S32_MIN;
		else
		  uticp.m_value[j] = (u32) -uticp.m_value[j];
	      }
	    }
	}

      if (i < MAX_CLASS_PARAMETERS)
        parameters[i] = uticp;
    }

    m_name = name;
    m_arrayLength = arraylen;
    m_bitSize = bitsize;
    m_classParameterCount = parms;

    for (u32 i = 0; i < MAX_CLASS_PARAMETERS; ++i)
      if (i < m_classParameterCount)
        m_classParameters[i] = parameters[i];

    return true;
  }