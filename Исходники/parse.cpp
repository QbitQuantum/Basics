void Match(sInt tok)
{
  if(Token!=tok)
    Error("Match Error");
  Out(Value);
  Scan();
}