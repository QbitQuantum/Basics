bool CodeGeneratorVisitor::performStep(ASTNode& node)
{
   node.accept(*this);

   return true;
}