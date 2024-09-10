Expression::Ptr ExpressionFactory::createExpression(const QString &expr,
                                                    const StaticContext::Ptr &context,
                                                    const LanguageAccent lang,
                                                    const SequenceType::Ptr &requiredType,
                                                    const QUrl &queryURI)
{
    pDebug() << Q_FUNC_INFO << queryURI;
    Q_ASSERT(context);
    Q_ASSERT(requiredType);
    Q_ASSERT(queryURI.isValid());

    OptimizationPasses::Coordinator::init();

    ParserContext::Ptr info(new ParserContext(context, lang,
                                              Tokenizer::Ptr(new XQueryTokenizer(expr, queryURI))));

    const int bisonRetval = XPathparse(info.data());

    Q_ASSERT_X(bisonRetval == 0, Q_FUNC_INFO,
               "We shouldn't be able to get an error, because we throw exceptions.");
    Q_UNUSED(bisonRetval); /* Needed when not compiled in debug mode, since bisonRetval won't
                            * be used in the Q_ASSERT_X above. */

    Expression::Ptr result(info->queryBody);

    if(!result)
    {
        context->error(QtXmlPatterns::tr("A library module cannot be evaluated "
                                         "directly. It must be imported from a "
                                         "main module."),
                       ReportContext::XPST0003,
                       QSourceLocation(queryURI, 1, 1));
    }

    /* Here, we type check user declared functions and global variables. This means
     * that variables and functions that are not used are type checked(which they otherwise
     * wouldn't have been), and those which are used, are type-checked twice, unfortunately. */

    const UserFunction::List::const_iterator end(info->userFunctions.constEnd());
    UserFunction::List::const_iterator it(info->userFunctions.constBegin());
    for(; it != end; ++it)
    {
        pDebug() << "-----      User Function Typecheck      -----";
        registerLastPath((*it)->body());

        /* We will most likely call body()->typeCheck() again, once for each callsite. That is, it will
         * be called from UserFunctionCallsite::typeCheck(), which will be called indirectly when
         * we check the query body. */
        const Expression::Ptr typeCheck((*it)->body()->typeCheck(context, (*it)->signature()->returnType()));
        /* We don't have to call (*it)->setBody(typeCheck) here since it's only used directly below. */
        processTreePass(typeCheck, UserFunctionTypeCheck);
        pDebug() << "------------------------------";

        pDebug() << "-----      User Function Compress      -----";
        const Expression::Ptr comp(typeCheck->compress(context));
        (*it)->setBody(comp);
        processTreePass(comp, UserFunctionCompression);
        pDebug() << "------------------------------";
    }

    const VariableDeclaration::Stack::const_iterator vend(info->variables.constEnd());
    VariableDeclaration::Stack::const_iterator vit(info->variables.constBegin());
    for(; vit != vend; ++vit)
    {
        Q_ASSERT(*vit);
        /* If it's already used, it will be typeChecked later on. */
        if((*vit)->isUsed() || (*vit)->type == VariableDeclaration::ExternalVariable)
            continue;

        pDebug() << "-----      Global Variable Typecheck      -----";
        Q_ASSERT((*vit)->expression());
        /* We supply ZeroOrMoreItems, meaning the variable can evaluate to anything. */
        // FIXME which is a source to bugs
        // TODO What about compressing variables?
        const Expression::Ptr
        nev((*vit)->expression()->typeCheck(context, CommonSequenceTypes::ZeroOrMoreItems));
        processTreePass(nev, GlobalVariableTypeCheck);
        pDebug() << "------------------------------";
    }

    pDebug() << "----- Initial AST build. -----";
    processTreePass(result, QueryBodyInitial);
    pDebug() << "------------------------------";

    pDebug() << "-----     Type Check     -----";
    registerLastPath(result);
    result->rewrite(result, result->typeCheck(context, requiredType), context);
    processTreePass(result, QueryBodyTypeCheck);
    pDebug() << "------------------------------";

    pDebug() << "-----      Compress      -----";
    result->rewrite(result, result->compress(context), context);
    processTreePass(result, QueryBodyCompression);
    pDebug() << "------------------------------";

    return result;
}