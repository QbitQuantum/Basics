sBool sShaderCompile(sCompileResult &result, sInt stype, sInt dtype, const sChar *source, sInt len, sInt flags /*=0*/, const sChar *name/*=0*/)
{
  for(sInt i=0;i<CompilerCount;i++)
  {
    if((ShaderCompiler[i].SrcType&(sSTF_PLATFORM|sSTF_PROFILE)) == (stype&(sSTF_PLATFORM|sSTF_PROFILE)) && (ShaderCompiler[i].DstType&(sSTF_PLATFORM|sSTF_PROFILE)) == (dtype&(sSTF_PLATFORM|sSTF_PROFILE)))
    {
      sChar8 *buffer = new sChar8[len];
      sCopyString(buffer,source,len);
      if(!name) name = L"main";
      sChar8 name8[64];
      sCopyString(name8,name,64);
      sBool check = (*ShaderCompiler[i].Func)(result,stype,dtype,flags,buffer,len,name8);
      sDeleteArray(buffer);
      return check;
    }
  }
  sPrintF(L"no shader compiler found for 0x%08x -> 0x%08x\n",stype,dtype);
  return sFALSE;
}