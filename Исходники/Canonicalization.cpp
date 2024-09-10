   AnsiString 
   RelaxedCanonicalization::CanonicalizeHeaderName(AnsiString name)
   {
      /*
      Unfold all header field continuation lines as described in
      [RFC2822]; in particular, lines with terminators embedded in
      continued header field values (that is, CRLF sequences followed by
      WSP) MUST be interpreted without the CRLF.  Implementations MUST
      NOT remove the CRLF at the end of the header field value.
      */

      name.ToLower();
      name.Trim();

      return name;
   }