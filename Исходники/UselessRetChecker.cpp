void UselessRetChecker::preCheckNode(const ast::Exp & e, SLintContext & context, SLintResult & result)
{
    if (e.isFunctionDec())
    {
        const ast::exps_t & rets = static_cast<const ast::FunctionDec &>(e).getReturns().getVars();
        useless.push(std::map<symbol::Symbol, Location>());
        std::map<symbol::Symbol, Location> & map = useless.top();
        for (const auto ret : rets)
        {
            const ast::SimpleVar & var = *static_cast<const ast::SimpleVar *>(ret);
            map.emplace(var.getSymbol(), var.getLocation());
        }
    }
    else if (e.isSimpleVar())
    {
        const ast::SimpleVar & var = static_cast<const ast::SimpleVar &>(e);
        if (context.isFunOut(var.getSymbol()) && context.isAssignedVar(var))
        {
            useless.top().erase(var.getSymbol());
        }
    }
}