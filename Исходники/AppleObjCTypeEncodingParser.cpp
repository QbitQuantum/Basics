std::string
AppleObjCTypeEncodingParser::ReadStructName(lldb_utility::StringLexer &type) {
  StreamString buffer;
  while (type.HasAtLeast(1) && type.Peek() != '=')
    buffer.Printf("%c", type.Next());
  return buffer.GetString();
}