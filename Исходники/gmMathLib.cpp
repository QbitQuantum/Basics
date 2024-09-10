static int GM_CDECL gmfATan(gmThread * a_thread)
{
  GM_CHECK_NUM_PARAMS(1);

  float floatValue;

  if(a_thread->ParamType(0) == GM_INT) { floatValue = (float) a_thread->Param(0).m_value.m_int; }
  else if(a_thread->ParamType(0) == GM_FLOAT) { floatValue = a_thread->Param(0).m_value.m_float; }
  else { return GM_EXCEPTION; }

  a_thread->PushFloat(atanf(floatValue));

  return GM_OK;
}