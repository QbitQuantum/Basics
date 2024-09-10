void postorder_traversal(const Basic &b, Visitor &v)
{
    for (const auto &p: b.get_args()) postorder_traversal(*p, v);
    b.accept(v);
}