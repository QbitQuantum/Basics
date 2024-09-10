FunctionScopePtr MethodStatement::onInitialParse(AnalysisResultPtr ar,
                                                 FileScopePtr fs,
                                                 bool method) {
  int minParam, maxParam;
  ConstructPtr self = shared_from_this();
  minParam = maxParam = 0;
  bool hasRef = false;
  if (m_params) {
    set<string> names;
    int i = 0;
    maxParam = m_params->getCount();
    for (; i < maxParam; i++) {
      ParameterExpressionPtr param =
        dynamic_pointer_cast<ParameterExpression>((*m_params)[i]);
      if (param->isRef()) hasRef = true;
      if (param->isOptional()) break;
      minParam++;
    }
    for (i++; i < maxParam; i++) {
      ParameterExpressionPtr param =
        dynamic_pointer_cast<ParameterExpression>((*m_params)[i]);
      if (param->isRef()) hasRef = true;
      if (!param->isOptional()) {
        Compiler::Error(Compiler::RequiredAfterOptionalParam, param);
        param->defaultToNull(ar);
      }
    }

    for (i = 0; i < maxParam; i++) {
      ParameterExpressionPtr param =
        dynamic_pointer_cast<ParameterExpression>((*m_params)[i]);
      if (names.find(param->getName()) == names.end()) {
        names.insert(param->getName());
      } else {
        Compiler::Error(Compiler::RedundantParameter, param);
        for (int j = 0; j < 1000; j++) {
          string name = param->getName() + lexical_cast<string>(j);
          if (names.find(name) == names.end()) {
            param->rename(name);
            break;
          }
        }
      }
    }
  }

  if (hasRef || m_ref) {
    m_attribute |= FileScope::ContainsReference;
  }

  StatementPtr stmt = dynamic_pointer_cast<Statement>(shared_from_this());
  FunctionScopePtr funcScope
    (new FunctionScope(ar, m_method, m_name, stmt, m_ref, minParam, maxParam,
                       m_modifiers, m_attribute, m_docComment, fs));
  if (!m_stmt) {
    funcScope->setVirtual();
  }
  setBlockScope(funcScope);

  return funcScope;
}