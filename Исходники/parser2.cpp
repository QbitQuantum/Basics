 Node * parseTerm() {
     if (lex.getToken() == LPAREN) {
         lex.next();
         Node * tmp = parseOR();
         assert(lex.getToken() == RPAREN);
         lex.next();
         return tmp;
     } 
     if (lex.getToken() == NOT) {
         lex.next();
         Node * tmp = parseTerm();
         return new Node("NOT", tmp, NULL);
     }
     if (lex.getToken() == VAR) {
         string v = lex.getVar();
         lex.next();
         return new Node(v);
     }
     assert(false);
 }