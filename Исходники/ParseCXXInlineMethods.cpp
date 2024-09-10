void Parser::ParseLexedMethodDeclaration(LateParsedMethodDeclaration &LM) {
  // If this is a member template, introduce the template parameter scope.
  ParseScope TemplateScope(this, Scope::TemplateParamScope, LM.TemplateScope);
  TemplateParameterDepthRAII CurTemplateDepthTracker(TemplateParameterDepth);
  if (LM.TemplateScope) {
    Actions.ActOnReenterTemplateScope(getCurScope(), LM.Method);
    ++CurTemplateDepthTracker;
  }
  // Start the delayed C++ method declaration
  Actions.ActOnStartDelayedCXXMethodDeclaration(getCurScope(), LM.Method);

  // Introduce the parameters into scope and parse their default
  // arguments.
  ParseScope PrototypeScope(this, Scope::FunctionPrototypeScope |
                            Scope::FunctionDeclarationScope | Scope::DeclScope);
  for (unsigned I = 0, N = LM.DefaultArgs.size(); I != N; ++I) {
    auto Param = LM.DefaultArgs[I].Param;
    // Introduce the parameter into scope.
    Actions.ActOnDelayedCXXMethodParameter(getCurScope(), Param);
    if (CachedTokens *Toks = LM.DefaultArgs[I].Toks) {
      // Mark the end of the default argument so that we know when to stop when
      // we parse it later on.
      Token LastDefaultArgToken = Toks->back();
      Token DefArgEnd;
      DefArgEnd.startToken();
      DefArgEnd.setKind(tok::eof);
      DefArgEnd.setLocation(LastDefaultArgToken.getLocation().getLocWithOffset(
          LastDefaultArgToken.getLength()));
      DefArgEnd.setEofData(Param);
      Toks->push_back(DefArgEnd);

      // Parse the default argument from its saved token stream.
      Toks->push_back(Tok); // So that the current token doesn't get lost
      PP.EnterTokenStream(&Toks->front(), Toks->size(), true, false);

      // Consume the previously-pushed token.
      ConsumeAnyToken();

      // Consume the '='.
      assert(Tok.is(tok::equal) && "Default argument not starting with '='");
      SourceLocation EqualLoc = ConsumeToken();

      // The argument isn't actually potentially evaluated unless it is
      // used.
      EnterExpressionEvaluationContext Eval(Actions,
                                            Sema::PotentiallyEvaluatedIfUsed,
                                            Param);

      ExprResult DefArgResult;
      if (getLangOpts().CPlusPlus11 && Tok.is(tok::l_brace)) {
        Diag(Tok, diag::warn_cxx98_compat_generalized_initializer_lists);
        DefArgResult = ParseBraceInitializer();
      } else
        DefArgResult = ParseAssignmentExpression();
      DefArgResult = Actions.CorrectDelayedTyposInExpr(DefArgResult);
      if (DefArgResult.isInvalid()) {
        Actions.ActOnParamDefaultArgumentError(Param, EqualLoc);
      } else {
        if (Tok.isNot(tok::eof) || Tok.getEofData() != Param) {
          // The last two tokens are the terminator and the saved value of
          // Tok; the last token in the default argument is the one before
          // those.
          assert(Toks->size() >= 3 && "expected a token in default arg");
          Diag(Tok.getLocation(), diag::err_default_arg_unparsed)
            << SourceRange(Tok.getLocation(),
                           (*Toks)[Toks->size() - 3].getLocation());
        }
        Actions.ActOnParamDefaultArgument(Param, EqualLoc,
                                          DefArgResult.get());
      }

      // There could be leftover tokens (e.g. because of an error).
      // Skip through until we reach the 'end of default argument' token.
      while (Tok.isNot(tok::eof))
        ConsumeAnyToken();

      if (Tok.is(tok::eof) && Tok.getEofData() == Param)
        ConsumeAnyToken();

      delete Toks;
      LM.DefaultArgs[I].Toks = nullptr;
    }
  }

  // Parse a delayed exception-specification, if there is one.
  if (CachedTokens *Toks = LM.ExceptionSpecTokens) {
    // Add the 'stop' token.
    Token LastExceptionSpecToken = Toks->back();
    Token ExceptionSpecEnd;
    ExceptionSpecEnd.startToken();
    ExceptionSpecEnd.setKind(tok::eof);
    ExceptionSpecEnd.setLocation(
        LastExceptionSpecToken.getLocation().getLocWithOffset(
            LastExceptionSpecToken.getLength()));
    ExceptionSpecEnd.setEofData(LM.Method);
    Toks->push_back(ExceptionSpecEnd);

    // Parse the default argument from its saved token stream.
    Toks->push_back(Tok); // So that the current token doesn't get lost
    PP.EnterTokenStream(&Toks->front(), Toks->size(), true, false);

    // Consume the previously-pushed token.
    ConsumeAnyToken();

    // C++11 [expr.prim.general]p3:
    //   If a declaration declares a member function or member function
    //   template of a class X, the expression this is a prvalue of type
    //   "pointer to cv-qualifier-seq X" between the optional cv-qualifer-seq
    //   and the end of the function-definition, member-declarator, or
    //   declarator.
    CXXMethodDecl *Method;
    if (FunctionTemplateDecl *FunTmpl
          = dyn_cast<FunctionTemplateDecl>(LM.Method))
      Method = cast<CXXMethodDecl>(FunTmpl->getTemplatedDecl());
    else
      Method = cast<CXXMethodDecl>(LM.Method);

    Sema::CXXThisScopeRAII ThisScope(Actions, Method->getParent(),
                                     Method->getTypeQualifiers(),
                                     getLangOpts().CPlusPlus11);

    // Parse the exception-specification.
    SourceRange SpecificationRange;
    SmallVector<ParsedType, 4> DynamicExceptions;
    SmallVector<SourceRange, 4> DynamicExceptionRanges;
    ExprResult NoexceptExpr;
    CachedTokens *ExceptionSpecTokens;

    ExceptionSpecificationType EST
      = tryParseExceptionSpecification(/*Delayed=*/false, SpecificationRange,
                                       DynamicExceptions,
                                       DynamicExceptionRanges, NoexceptExpr,
                                       ExceptionSpecTokens);

    if (Tok.isNot(tok::eof) || Tok.getEofData() != LM.Method)
      Diag(Tok.getLocation(), diag::err_except_spec_unparsed);

    // Attach the exception-specification to the method.
    Actions.actOnDelayedExceptionSpecification(LM.Method, EST,
                                               SpecificationRange,
                                               DynamicExceptions,
                                               DynamicExceptionRanges,
                                               NoexceptExpr.isUsable()?
                                                 NoexceptExpr.get() : nullptr);

    // There could be leftover tokens (e.g. because of an error).
    // Skip through until we reach the original token position.
    while (Tok.isNot(tok::eof))
      ConsumeAnyToken();

    // Clean up the remaining EOF token.
    if (Tok.is(tok::eof) && Tok.getEofData() == LM.Method)
      ConsumeAnyToken();

    delete Toks;
    LM.ExceptionSpecTokens = nullptr;
  }

  PrototypeScope.Exit();

  // Finish the delayed C++ method declaration.
  Actions.ActOnFinishDelayedCXXMethodDeclaration(getCurScope(), LM.Method);
}