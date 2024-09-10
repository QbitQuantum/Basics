void EmptyBlockChecker::preCheckNode(const ast::Exp & e, SLintContext & context, SLintResult & result)
{
    if (e.isSeqExp())
    {
        const ast::exps_t & exps = static_cast<const ast::SeqExp &>(e).getExps();
        bool empty = exps.empty();
        if (!empty)
        {
            empty = true;
            for (const auto exp : exps)
            {
                if (!exp->isCommentExp())
                {
                    empty = false;
                    break;
                }
            }
        }

        if (empty)
        {
            result.report(context, e.getLocation(), *this, _("Empty block."));
        }
    }
}