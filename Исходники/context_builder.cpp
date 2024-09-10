    shared_ptr<Term> ContextBuilder::buildMethodBody(
        const shared_ptr<MethodTerm> &term) {

        LexerTermBuilder builder;
        term->accept(&builder);

        return builder.getTerm();
    }