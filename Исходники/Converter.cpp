//-----------------------------------------------------------------------------------
 Integer Converter::ToInteger(std::string &polynom) {
   Integer result;
   if(polynom.length() != 0) {
      int last_nonzero = polynom.find_last_of("1");
      result.Pow(2,last_nonzero);
   }
  return result;
 }