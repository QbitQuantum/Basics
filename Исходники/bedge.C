bool
Bedge::is_chain_tip(CSimplexFilter& filter) const
{
    return (filter.accept((Bedge*)this) &&
            (_v1->degree(filter) != 2 || _v2->degree(filter) != 2));
}