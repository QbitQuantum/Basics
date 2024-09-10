// Expecting optional = sign, or the start of the value
bool XLEMapInfoParser::doStateExpectEqual(XLTokenizer &tokenizer)
{
   if(tokenizer.getToken() == "=")
   {
      // found an optional =, expect value.
      state = STATE_EXPECTVALUE;
      return true;
   }
   else
   {
      // otherwise, this is the value token; process it immediately
      return doStateExpectValue(tokenizer);
   }
}