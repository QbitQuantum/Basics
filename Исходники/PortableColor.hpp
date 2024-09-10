 constexpr RGB8Color Lighten() const {
   return Invert().Darken().Invert();
 }