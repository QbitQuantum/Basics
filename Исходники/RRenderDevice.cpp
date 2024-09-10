MO_NAMESPACE_BEGIN

//============================================================
// <T>½âÎö×Ö·û´®ÎªÃ¶¾ÙÄÚÈÝ¡£</T>
//
// @param pValue ×Ö·û´®
// @param deviceCd Ä¬ÈÏÄÚÈÝ
// @return Ã¶¾ÙÄÚÈÝ
//============================================================
ERenderDevice RRenderDevice::Parse(TCharC* pValue, ERenderDevice deviceCd){
   if(pValue != NULL){
      TFsCode code = pValue;
      code.ToLower();
      if(code.Equals("unknown")){
         return ERenderDevice_Unknown;
      }else if(code.Equals("directx9")){
         return ERenderDevice_DirectX9;
      }else if(code.Equals("directx10")){
         return ERenderDevice_DirectX10;
      }else if(code.Equals("directx11")){
         return ERenderDevice_DirectX11;
      }else if(code.Equals("opengl2")){
         return ERenderDevice_OpenGL2;
      }else if(code.Equals("opengl3")){
         return ERenderDevice_OpenGL3;
      }else if(code.Equals("opengl4")){
         return ERenderDevice_OpenGL4;
      }else if(code.Equals("opengles2")){
         return ERenderDevice_OpenGLEs2;
      }else if(code.Equals("opengles3")){
         return ERenderDevice_OpenGLEs3;
      }else{
         MO_STATIC_FATAL("Parse render device failure. (value=%s)", pValue);
      }
   }
   return deviceCd;
}