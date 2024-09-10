 std::string SystemException::GetErrorCodeString(int code) {
   std::wstring error(_wcserror(code));
   return atom::ConvertUTF<char>(error);
 }