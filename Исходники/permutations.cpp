// Adds one to the little-endian representation of an integer in base digits,
// returns true if there was an overflow
static bool addOne(Vec<long>& rep, const Vec<long> digits)
{
  for (long i=rep.length()-1; i>=0; --i) {
    rep[i]++;
    if (rep[i] >= digits[i])
      rep[i] -= digits[i];
    else
      return false;
  }
  return true;
}