int RNY::getRNY(int i, int j, int k, const Alphabet& alph) const throw (BadCharException)
{
  if (alph.getAlphabetType() != "DNA alphabet")
  {
    throw AlphabetException ("RNY::getRNY : Sequence must be DNA",
                             &alph);
  }

  char li = alph.intToChar(i)[0];
  char lj = alph.intToChar(j)[0];
  char lk = alph.intToChar(k)[0];

  int r = 0;
  int s = 0;

  switch (li)
  {
  case 'A':
  case 'G':
    r += 0;
    break;
  case 'C':
    r += 1;
    break;
  case 'T':
    r += 2;
    break;
  case '-':
  case 'N':
    s += 1;
    break;
  default:
    throw BadCharException(&li, "RNY::getRNY(int,int;int,alph): Specified base unknown.");
  }

  r *= 4;
  s *= 2;

  switch (lj)
  {
  case 'A':
    r += 0;
    break;
  case 'G':
    r += 1;
    break;
  case 'C':
    r += 2;
    break;
  case 'T':
    r += 3;
    break;
  case '-':
  case 'N':
    s += 1;
    break;
  default:
    throw BadCharException(&lj, "RNY::getRNY(int,int;int,alph): Specified base unknown.");
  }

  r *= 3;
  s *= 2;

  switch (lk)
  {
  case 'A':
    r += 0;
    break;
  case 'G':
    r += 1;
    break;
  case 'C':
  case 'T':
    r += 2;
    break;
  case '-':
  case 'N':
    s += 1;
    break;
  default:
    throw BadCharException(&lk, "RNY::getRNY(int,int;int,alph): Specified base unknown.");
  }

  return 50 * s + r;
}