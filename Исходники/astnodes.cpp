void ASTNodes::accept(ASTVisitor& visitor)
{
   for ( std::size_t index = 0; index < mNodes.size(); index++ )
   {
      ASTNode* pnode = mNodes[index];
      pnode->accept(visitor);
   }
}