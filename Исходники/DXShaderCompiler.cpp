bool DXShaderCompiler::CompileShader(const std::string& source_file,
                                     const std::string& entry_point,
                                     const char* target,
                                     ShaderOpt opt_level, bool debug,
                                     const ShaderDefine* defines,
                                     size_t num_defines,
                                     std::vector<uint8_t>& output,
                                     YFileUtils::FileEnv* file_env) {
  std::string work_dir = YFileUtils::FilePath::DirPath(source_file);
  const std::vector<uint8_t>* source_data = GetFileData(source_file, file_env);

  std::vector<D3D_SHADER_MACRO> macros;
  for (size_t i = 0; i < num_defines; ++i) {
    macros.push_back({defines[i].define, defines[i].value});
  }
  macros.push_back({NULL, NULL});

  DXIncludeData include_data(work_dir, file_env);

  UINT flags1 = D3DCOMPILE_WARNINGS_ARE_ERRORS;
  switch (opt_level) {
   case kShaderOpt_None: flags1 |= D3DCOMPILE_SKIP_OPTIMIZATION; break;
   case kShaderOpt_Level0: flags1 |= D3DCOMPILE_OPTIMIZATION_LEVEL0; break;
   case kShaderOpt_Level1: flags1 |= D3DCOMPILE_OPTIMIZATION_LEVEL1; break;
   case kShaderOpt_Level2: flags1 |= D3DCOMPILE_OPTIMIZATION_LEVEL2; break;
   case kShaderOpt_Level3: flags1 |= D3DCOMPILE_OPTIMIZATION_LEVEL3; break;
   default:
     std::cerr << "Invalid Shader Opt: " << opt_level << std::endl;
     return false;
  }

  if (debug) {
    flags1 |= D3DCOMPILE_DEBUG;
  }

  ID3DBlob* code;
  ID3DBlob* error_msgs;

  HRESULT ret = D3DCompile2(
      source_data->data(), // in   LPCVOID pSrcData,
      source_data->size(), // in   SIZE_T SrcDataSize,
      source_file.c_str(), // in   LPCSTR pSourceName,
      macros.data(),       // in   const D3D_SHADER_MACRO *pDefines,
      &include_data,       // in   ID3DInclude *pInclude,
      entry_point.c_str(), // in   LPCSTR pEntrypoint,
      target,              // in   LPCSTR pTarget,
      flags1,              // in   UINT Flags1,
      0,                   // in   UINT Flags2,
      0,                   // in   UINT SecondaryDataFlags,
      NULL,                // in   LPCVOID pSecondaryData,
      0,                   // in   SIZE_T SecondaryDataSize,
      &code,               // out  ID3DBlob **ppCode,
      &error_msgs          // out  ID3DBlob **ppErrorMsgs
      );

  if (FAILED(ret)) {
    std::cerr << "[ERROR] "
              << static_cast<const char*>(error_msgs->GetBufferPointer())
              << std::endl;
    return false;
  }

  size_t code_size = code->GetBufferSize();
  output.resize(code_size);
  memcpy(output.data(), code->GetBufferPointer(), code_size);
  return true;
}