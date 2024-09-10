MO_NAMESPACE_BEGIN

//============================================================
// <T>½âÎö×Ö·û´®ÎªÃ¶¾ÙÄÚÈÝ¡£</T>
//
// @param pValue ×Ö·û´®
// @param bufferCd Ä¬ÈÏÄÚÈÝ
// @return Ã¶¾ÙÄÚÈÝ
//============================================================
ERenderShaderBuffer RRenderShaderBuffer::Parse(TCharC* pValue, ERenderShaderBuffer bufferCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("globalstatic")){
         return ERenderShaderBuffer_GlobalStatic;
      }else if(code.Equals("globaldynamic")){
         return ERenderShaderBuffer_GlobalDynamic;
      }else if(code.Equals("techniquestatic")){
         return ERenderShaderBuffer_TechniqueStatic;
      }else if(code.Equals("techniquedynamic")){
         return ERenderShaderBuffer_TechniqueDynamic;
      }else if(code.Equals("effectstatic")){
         return ERenderShaderBuffer_EffectStatic;
      }else if(code.Equals("effectdynamic")){
         return ERenderShaderBuffer_EffectDynamic;
      }else if(code.Equals("renderabledynamic")){
         return ERenderShaderBuffer_RenderableDynamic;
      }else if(code.Equals("renderablematerial")){
         return ERenderShaderBuffer_RenderableMaterial;
      }else{
         MO_STATIC_FATAL("Parse shader buffer type failure. (value=%s)", pValue);
      }
   }
   return bufferCd;
}