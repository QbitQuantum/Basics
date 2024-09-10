void
ToUpperCase(nsAString& aString)
{
  PRUnichar *buf = aString.BeginWriting();
  ToUpperCase(buf, buf, aString.Length());
}