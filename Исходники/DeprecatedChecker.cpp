void DeprecatedChecker::__Svd::preCheckNode(const ast::Exp & e, SLintContext & context, SLintResult & result)
{
    const ast::CallExp & ce = static_cast<const ast::CallExp &>(e);
    const ast::exps_t args = ce.getArgs();
    if (args.size() == 2)
    {
        const ast::Exp & second = *args.back();
        if (second.isDoubleExp() && static_cast<const ast::DoubleExp &>(second).getValue() == 0)
        {
            result.report(context, e.getLocation(), *this, _("svd(..., 0) is deprecated."));
        }
    }
}