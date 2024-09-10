 const char16* JavascriptSIMDBool8x16::GetFullBuiltinName(char16** aBuffer, const char16* name)
 {
     Assert(aBuffer && *aBuffer);
     swprintf_s(*aBuffer, SIMD_STRING_BUFFER_MAX, _u("SIMD.Bool8x16.%s"), name);
     return *aBuffer;
 }