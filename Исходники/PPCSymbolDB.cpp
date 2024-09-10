void PPCSymbolDB::AddKnownSymbol(u32 startAddr, u32 size, const std::string& name,
                                 Common::Symbol::Type type)
{
  auto iter = m_functions.find(startAddr);
  if (iter != m_functions.end())
  {
    // already got it, let's just update name, checksum & size to be sure.
    Common::Symbol* tempfunc = &iter->second;
    tempfunc->Rename(name);
    tempfunc->hash = HashSignatureDB::ComputeCodeChecksum(startAddr, startAddr + size - 4);
    tempfunc->type = type;
    tempfunc->size = size;
  }
  else
  {
    // new symbol. run analyze.
    Common::Symbol tf;
    tf.Rename(name);
    tf.type = type;
    tf.address = startAddr;
    if (tf.type == Common::Symbol::Type::Function)
    {
      PPCAnalyst::AnalyzeFunction(startAddr, tf, size);
      // Do not truncate symbol when a size is expected
      if (size != 0 && tf.size != size)
      {
        WARN_LOG(SYMBOLS, "Analysed symbol (%s) size mismatch, %u expected but %u computed",
                 name.c_str(), size, tf.size);
        tf.size = size;
      }
      m_checksum_to_function[tf.hash].insert(&m_functions[startAddr]);
    }
    else
    {
      tf.size = size;
    }
    m_functions[startAddr] = tf;
  }
}