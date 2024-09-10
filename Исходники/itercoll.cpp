void CollationIteratorTest::TestUnicodeChar()
{
    CollationElementIterator *iter;
    UChar codepoint;
    UnicodeString source;
    
    for (codepoint = 1; codepoint < 0xFFFE;)
    {
      source.remove();

      while (codepoint % 0xFF != 0) 
      {
        if (u_isdefined(codepoint))
          source += codepoint;
        codepoint ++;
      }

      if (u_isdefined(codepoint))
        source += codepoint;
      
      if (codepoint != 0xFFFF)
        codepoint ++;

      iter = en_us->createCollationElementIterator(source);
      /* A basic test to see if it's working at all */
      backAndForth(*iter);
      delete iter;
    }
}