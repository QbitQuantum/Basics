bool ValueProcessor::needsProcessing(const TokenList &value) const {
  TokenList::const_iterator i;
  const Token *t;
  string operators("+-*/");

  for (i = value.begin(); i != value.end(); i++) {
    // variable
    if ((*i).type == Token::ATKEYWORD ||
        // url
        (*i).type == Token::URL ||
        // operator
        operators.find(*i) != string::npos) {
      return true;

    } else {
      if (*i == "~") {
        if ((*++i).type == Token::STRING)
          return true;
        else
          i--;

      } else if ((*i).type == Token::IDENTIFIER || (*i).type == Token::OTHER) {
        // function
        t = &(*i);
        i++;
        if (i != value.end() && (*i).type == Token::PAREN_OPEN &&
            functionExists((*t).c_str())) {
          return true;
        } else
          i--;
      }
    }
  }

  return false;
}