// Expecting the name of a sky texture
bool XLMapInfoParser::doStateExpectSkyName(XLTokenizer &token)
{
   curInfo->setString(kwd->key, token.getToken().constPtr());
   state = STATE_EXPECTSKYNUM;
   return true;
}