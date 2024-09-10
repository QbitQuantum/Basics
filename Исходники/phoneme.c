static int
isconsonant(char chr)
{
  return (isupper((int)chr) && !isvowel(chr));
}