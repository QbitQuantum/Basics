void QualType::getAsStringInternal(const Type *ty, Qualifiers qs,
                                   std::string &buffer,
                                   const PrintingPolicy &policy) {
  SmallString<256> Buf;
  llvm::raw_svector_ostream StrOS(Buf);
  TypePrinter(policy).print(ty, qs, StrOS, buffer);
  std::string str = StrOS.str();
  buffer.swap(str);
}