void FunctionArgsOrderChecker::preCheckNode(const ast::Exp & e, SLintContext & context, SLintResult & result)
{
    const ast::CallExp & ce = static_cast<const ast::CallExp &>(e);
    if (ce.getName().isSimpleVar())
    {
        ast::exps_t args = ce.getArgs();
        std::map<symbol::Symbol, unsigned int> assignments;
        unsigned int pos = 1;
        for (const auto arg : args)
        {
            if (arg->isAssignExp())
            {
                const ast::AssignExp & ae = *static_cast<const ast::AssignExp *>(arg);
                if (ae.getLeftExp().isSimpleVar())
                {
                    assignments.emplace(static_cast<ast::SimpleVar &>(ae.getLeftExp()).getSymbol(), pos);
                }
            }
            else if (!assignments.empty())
            {
                result.report(context, e.getLocation(), *this, _("Argument at position %d must be an assignment."), pos);
            }
            ++pos;
        }
        if (!assignments.empty())
        {
            const std::wstring & name = static_cast<const ast::SimpleVar &>(ce.getName()).getSymbol().getName();
            const ast::FunctionDec * fundec = context.getPublicFunction(name);
            if (!fundec)
            {
                fundec = context.getPrivateFunction(name);
            }

            if (fundec)
            {
                const ast::exps_t & funargs = fundec->getArgs().getVars();
                pos = 1;
                for (const auto arg : funargs)
                {
                    const symbol::Symbol & sym = static_cast<const ast::SimpleVar *>(arg)->getSymbol();
                    auto i = assignments.find(sym);
                    if (i != assignments.end())
                    {
                        if (pos != i->second)
                        {
                            result.report(context, e.getLocation(), *this, _("Argument %s declared at position %d and assigned at position %d."), sym.getName(), pos, i->second);
                        }
                    }
                    ++pos;
                }
            }
        }
    }
}