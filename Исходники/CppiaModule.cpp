void CppiaConst::fromStream(CppiaStream &stream)
{
   std::string tok = stream.getToken();
   if (tok[0]=='i')
   {
      type = cInt;

      dval = ival = stream.getInt();
   }
   else if (tok=="true")
   {
      type = cInt;
      dval = ival = 1;
   }
   else if (tok=="false")
   {
      type = cInt;
      dval = ival = 0;
   }
   else if (tok[0]=='f')
   {
      type = cFloat;
      int strIndex = stream.getInt();
      String val = stream.module->strings[strIndex];
      dval = atof(val.__s);
      ival = dval;
   }
   else if (tok[0]=='s')
   {
      type = cString;
      ival = stream.getInt();
   }
   else if (tok=="NULL")
      type = cNull;
   else if (tok=="THIS")
      type = cThis;
   else if (tok=="SUPER")
      type = cSuper;
   else
      throw "unknown const value";
}