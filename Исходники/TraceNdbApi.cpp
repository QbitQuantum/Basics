int CTraceNdbSchemaOp::createAttribute(const char* aAttrName, KeyType aTupleyKey)
{
  int i = NdbSchemaOp::createAttribute(aAttrName, aTupleyKey);
  TraceBegin();
  TraceNdbSchemaOp(this);
  TraceMethod("createAttribute");
  TraceString(aAttrName);
  TraceKeyType(aTupleyKey);
  TraceReturn();
  TraceInt(i);
  TraceEnd();
  return i;
}