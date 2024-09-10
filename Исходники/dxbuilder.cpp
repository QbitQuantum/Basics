void DxBuilder::buildPixelShader(const ASTEffect& effect, ASTTechnique& technique)
{
   const ASTFunction* pfunction = effect.findFunction(technique.mPixel.mEntry);

   String code = UTEXT("// generated pixel shader\n\n");

   String num;
   NumberConverter& conv = NumberConverter::getInstance();
   for ( std::size_t index = 0; index < effect.mTextures.size(); ++index )
   {
      ASTTexture* ptexture = effect.mTextures[index];
      code += UTEXT("Texture2D ") + ptexture->mName + UTEXT(" : register(t");

      int reg = ptexture->mRegister;
      if ( reg == -1 )
      {
         reg = (int) index;
      }
      
      code += conv.format(num, reg) + UTEXT(");\n");
      num = UTEXT("");
   }

   for ( std::size_t index = 0; index < effect.mSamplers.size(); ++index )
   {
      ASTSampler* psampler = effect.mSamplers[index];
      code += UTEXT("SamplerState ") + psampler->mName + UTEXT(" : register(s");
      
      int reg = psampler->mRegister;
      if ( reg == -1 )
      {
         reg = index;
      }
      
      code += conv.format(num, (int)reg) + UTEXT(");\n");
      num = UTEXT("");
   }

   code += buildStructs(effect, *pfunction);
   code += buildFunction(*pfunction);

   std::string data = code.toUtf8();
   std::string entry = technique.mPixel.mEntry.toUtf8();
   std::string target = technique.mPixel.mTarget.toUtf8();
   uint32_t flags = D3DCOMPILE_ENABLE_STRICTNESS;

   ID3DBlob *presult, *perror;
   HRESULT hr = D3DCompile(data.c_str(), data.length(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), target.c_str(), flags, 0, &presult, &perror);
   if ( FAILED(hr) )
   {
      std::string d3derror = "Shader compile error: " + std::string((const char*)perror->GetBufferPointer());
      throw std::exception(d3derror.c_str());
   }
      
   technique.mPixel.mCompiledCode.writeBlob(presult->GetBufferPointer(), presult->GetBufferSize());
}