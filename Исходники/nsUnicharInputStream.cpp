 explicit StringUnicharInputStream(const nsAString& aString) :
   mString(aString), mPos(0), mLen(aString.Length()) { }