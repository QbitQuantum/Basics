 void MzTabBoolean::fromCellString(const String& s)
 {
   String lower = s;
   lower.toLower().trim();
   if (lower == "null")
   {
     setNull(true);
   }
   else
   {
     if (s == "0")
     {
       set(false);
     }
     else if (s == "1")
     {
       set(true);
     }
     else
     {
       throw Exception::ConversionError(__FILE__, __LINE__, __PRETTY_FUNCTION__, String("Could not convert String '") + s + "' to MzTabBoolean");
     }
   }
 }