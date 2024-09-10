bool VariableCheckVisitor::isVariableImpl(const ASTNode& node)
{
   node.accept(*this);
   return mVariable;
}