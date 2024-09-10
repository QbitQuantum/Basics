UCharCharacterIterator::UCharCharacterIterator(const UChar* textPtr,
                                               int32_t length)
  : CharacterIterator(textPtr != 0 ? (length>=0 ? length : u_strlen(textPtr)) : 0),
  text(textPtr)
{
}