 void AssertStringsEqual(HSTRING a, HSTRING b)
 {
     std::wstring s1 = WindowsGetStringRawBuffer(a, nullptr);
     std::wstring s2 = WindowsGetStringRawBuffer(b, nullptr);
     Assert::AreEqual(s1, s2);
 }