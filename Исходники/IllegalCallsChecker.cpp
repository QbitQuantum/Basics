void IllegalCallsChecker::preCheckNode(const ast::Exp & e, SLintContext & context, SLintResult & result)
{
    if (e.getParent()->isCallExp() || e.getParent()->isSeqExp())
    {
        const std::wstring & name = static_cast<const ast::SimpleVar &>(e).getSymbol().getName();
        if (illegal.find(name) != illegal.end())
        {
            result.report(context, e.getLocation(), *this, _("Illegal call: %s."), name);
        }
    }
}