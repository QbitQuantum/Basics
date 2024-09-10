 int64 ConvertStringToInt64(Var string, ScriptContext* scriptContext)
 {
     JavascriptString* str = JavascriptString::FromVar(string);
     charcount_t length = str->GetLength();
     const char16* buf = str->GetString();
     int radix = 10;
     if (length >= 2 && buf[0] == '0' && buf[1] == 'x')
     {
         radix = 16;
     }
     return (int64)_wcstoui64(buf, nullptr, radix);
 }