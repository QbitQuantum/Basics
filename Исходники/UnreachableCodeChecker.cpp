void UnreachableCodeChecker::preCheckNode(const ast::Exp & e, SLintContext & context, SLintResult & result)
{
    const ast::exps_t & exps = e.getExps();
    const ast::Exp * returnExp = nullptr;
    for (const auto exp : exps)
    {
        if (returnExp)
        {
            if (!exp->isCommentExp())
            {
                result.report(context, returnExp->getLocation(), *this, _("The code after the return statement is unreachable."));
                return;
            }
        }
        else if (exp->isReturnExp())
        {
            returnExp = exp;
        }
    }
}