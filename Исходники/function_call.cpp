FunctionCall::FunctionCall
(EXPRESSION_CONSTRUCTOR_BASE_PARAMETERS,
 ExpressionPtr nameExp, const std::string &name, bool hadBackslash,
 ExpressionListPtr params, ExpressionPtr classExp)
    : Expression(EXPRESSION_CONSTRUCTOR_BASE_PARAMETER_VALUES),
      StaticClassName(classExp),
      m_nameExp(nameExp),
      m_params(params),
      m_valid(false),
      m_variableArgument(false),
      m_redeclared(false),
      m_arrayParams(false),
      m_hadBackslash(hadBackslash) {

    if (m_nameExp &&
            m_nameExp->getKindOf() == Expression::KindOfScalarExpression) {
        assert(m_origName.empty());
        ScalarExpressionPtr c = dynamic_pointer_cast<ScalarExpression>(m_nameExp);
        m_origName = c->getOriginalLiteralString();
        c->toLower(true /* func call*/);
    } else {
        m_origName = name;
    }
}