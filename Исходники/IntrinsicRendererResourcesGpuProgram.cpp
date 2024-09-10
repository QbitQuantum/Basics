void saveShaderCache()
{
  FILE* fp = fopen(_shaderCacheFilePath.c_str(), "wb");

  if (fp == nullptr)
  {
    _INTR_LOG_ERROR("Failed to save shader cache...");
    return;
  }

  char* writeBuffer = (char*)Memory::Tlsf::MainAllocator::allocate(65536u);
  {
    rapidjson::FileWriteStream os(fp, writeBuffer, 65536u);
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
    _shaderCache.Accept(writer);
    fclose(fp);
  }
  Memory::Tlsf::MainAllocator::free(writeBuffer);
}