 JavascriptString* JavascriptTypedNumber<unsigned __int64>::ToString(Var value, ScriptContext* scriptContext)
 {
     char16 szBuffer[30];
     unsigned __int64 val = JavascriptUInt64Number::FromVar(value)->GetValue();
     errno_t err = _ui64tow_s(val, szBuffer, 30, 10);
     AssertMsg(err == 0, "convert int64 to string failed");
     return JavascriptString::NewCopySz(szBuffer, scriptContext);
 }