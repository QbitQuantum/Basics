Node<ExpressionNode>::Link ExpressionParser::expressionImpl(Node<ExpressionNode>::Link lhs, int minPrecedence) {
  Node<ExpressionNode>::Link base = nullptr;
  
  Node<ExpressionNode>::Link lastExpr = nullptr;
  Token tok = current();
  if (acceptEndOfExpression()) return lhs;
  if (lhs != nullptr) {
    skip(-1);
    auto tt = current().type;
    skip(1);
    // If we have any of:
    // IDENTIFIER, C_PAREN_RIGHT, postfix ops
    // before a paren, it's a function call
    auto isCallable =
      tt == TT::IDENTIFIER ||
      tt == TT::PAREN_RIGHT ||
      (tt == TT::OPERATOR && lhs->getToken().op().hasFixity(POSTFIX));
    if (accept(TT::PAREN_LEFT) && isCallable) {
      auto fCall = parseExpressionPrimary(true);
      auto args = fCall->removeChild(0);
      fCall->addChild(lhs);
      fCall->addChild(args);
      lhs = fCall;
      // If the expression finishes here, return
      if (acceptEndOfExpression()) return lhs;
      // Otherwise, update tok
      tok = current();
    }
  }
  while (tok.op().hasArity(BINARY) && tok.op().getPrec() >= minPrecedence) {
    auto tokExpr = Node<ExpressionNode>::make(tok);
    tokExpr->setTrace(tok.trace);
    tokExpr->addChild(lhs);
    skip();
    auto rhs = parseExpressionPrimary();
    tok = current();
    while (tok.isOp() && tok.op().hasArity(BINARY) &&
      (
        tok.op().getPrec() <= tokExpr->getToken().op().getPrec() ||
        (tok.op().getPrec() == tokExpr->getToken().op().getPrec() && tok.op().hasAsoc(ASSOCIATE_FROM_RIGHT))
      )
    ) {
      tokExpr->addChild(rhs);
      tokExpr = expressionImpl(tokExpr, tok.op().getPrec());
      rhs = nullptr;
      tok = current();
    }
    lhs = rhs;
    if (base == nullptr) {
      base = lastExpr = tokExpr;
    } else {
      lastExpr->addChild(tokExpr);
      lastExpr = tokExpr;
    }
    if (acceptEndOfExpression()) break;
  }
  if (base == nullptr) {
    base = lhs;
  } else if (lhs != nullptr) {
    lastExpr->addChild(lhs);
  }
  return base;
}