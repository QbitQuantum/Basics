void ExpressionList::toLower() {
  for (unsigned int i = 0; i < m_exps.size(); i++) {
    ScalarExpressionPtr s = dynamic_pointer_cast<ScalarExpression>(m_exps[i]);
    s->toLower();
  }
}