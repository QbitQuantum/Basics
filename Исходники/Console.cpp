  void
  Initialize(JSContext* aCx, Console::MethodName aName,
             const nsAString& aString, const Sequence<JS::Value>& aArguments)
  {
    mGlobal = JS::CurrentGlobalOrNull(aCx);
    mMethodName = aName;
    mMethodString = aString;

    for (uint32_t i = 0; i < aArguments.Length(); ++i) {
      mArguments.AppendElement(aArguments[i]);
    }
  }