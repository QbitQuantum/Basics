 void mirrorCharacters(UChar* destination, const UChar* source, int length) const
 {
     int position = 0;
     bool error = false;
     // Iterate characters in source and mirror character if needed.
     while (position < length) {
         UChar32 character;
         int nextPosition = position;
         U16_NEXT(source, nextPosition, length, character);
         character = u_charMirror(character);
         U16_APPEND(destination, position, length, character, error);
         ASSERT(!error);
         position = nextPosition;
     }
 }