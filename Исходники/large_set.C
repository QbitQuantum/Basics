void LargeSet::remove (Elt elt)
{
    if (not contains(elt)) return;
    Set *r = new Set(*m_set);
    r->remove(elt);
    if (*r) { m_set.set(*r); return; }
    delete r; m_set.clear();
}