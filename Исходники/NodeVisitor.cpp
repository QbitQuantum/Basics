void NodeVisitor::visitDoLoop(const DoLoopPtr& node)
{
    ACCEPT(node->getCodeBlock());
    ACCEPT(node->getCondition());
}