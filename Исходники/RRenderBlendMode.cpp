MO_NAMESPACE_BEGIN

//============================================================
// <T>½âÎö×Ö·û´®ÎªÃ¶¾ÙÄÚÈÝ¡£</T>
//
// @param pValue ×Ö·û´®
// @param blendModeCd Ä¬ÈÏÄÚÈÝ
// @return Ã¶¾ÙÄÚÈÝ
//============================================================
ERenderBlendMode RRenderBlendMode::Parse(TCharC* pValue, ERenderBlendMode blendModeCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("none")){
         return ERenderBlendMode_None;
      }else if(code.Equals("sourcealpha")){
         return ERenderBlendMode_SourceAlpha;
      }else if(code.Equals("oneminussourcealpha")){
         return ERenderBlendMode_OneMinusSourceAlpha;
      }else{
         MO_STATIC_FATAL("Parse blend mode failure. (value=%s)", pValue);
      }
   }
   return blendModeCd;
}