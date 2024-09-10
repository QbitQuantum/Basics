bool fp_AnnotationRun::_setValue(void)
{
  UT_uint32 pos = getBlock()->getDocLayout()->getAnnotationVal(getPID()) + 1;
  UT_String tmp;
  UT_String_sprintf(tmp,"(%d)",pos);
  m_sValue = tmp.c_str();
  return true;
}