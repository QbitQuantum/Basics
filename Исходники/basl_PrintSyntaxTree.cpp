 void printSyntaxTree (std::ostream & os, Node & node)
 {
   Token const & token = node.getToken ();
   if (token.isSet ())
   {
     os << identToString (token.getLexeme ()) << '\n';
   }
   Nonterm const & nonterm = node.getNonterm ();
   if (nonterm.isSet ())
   {
     printSyntaxTree (os, nonterm);
   }
 }