ASTForm* DistributiveAntiPrenexer::existentialDistributiveAntiPrenex(ASTForm *form) {
    static_assert(std::is_base_of<ASTForm_q, ExistClass>::value, "ExistClass is not derived from 'ASTForm_q' class");

    // First call the anti-prenexing rule to push the quantifier as deep as possible
    //ASTForm* antiPrenexedForm = existentialAntiPrenex<ExistClass>(form);

    // Expand Universal Quantifier
    UniversalQuantifierRemover universalUnfolding;
    ASTForm* antiPrenexedForm = reinterpret_cast<ASTForm*>(form->accept(universalUnfolding));

    // Push negations down as well
    NegationUnfolder negationUnfolding;
    antiPrenexedForm = reinterpret_cast<ASTForm*>(antiPrenexedForm->accept(negationUnfolding));

    if(antiPrenexedForm->kind == aEx1 || antiPrenexedForm->kind == aEx2) {
        ExistClass* exForm = reinterpret_cast<ExistClass*>(antiPrenexedForm);
        switch(exForm->f->kind) {
            case aOr:
                return distributiveRule<ExistClass, ASTForm_Or>(exForm);
            case aAnd:
                return distributeDisjunction<ExistClass>(exForm);
            default:
                return antiPrenexedForm;
        }
    } else {
        // We are done
        return antiPrenexedForm;
    }
}