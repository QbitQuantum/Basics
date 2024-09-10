unsigned int AlphabetTools::getAlphabetCodingSize(const Alphabet& alphabet) throw (AlphabetException)
{
  if (!checkAlphabetCodingSize(alphabet))
    throw AlphabetException("Bad alphabet in function Alphabet::getAlphabetCodingSize().");
  return static_cast<unsigned int>(alphabet.intToChar(0).size());
}