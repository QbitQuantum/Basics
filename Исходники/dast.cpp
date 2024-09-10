void DebugPrintVisitor::generateTree(Node &node)
{
    for (int i = 0; i < step * depth; ++i)
    {
        os << indentChar;
    }
    node.accept(*this);
    ++depth;
    for (auto& child : node.childs())
    {
        if (child) generateTree(*child);
    }
    --depth;
}