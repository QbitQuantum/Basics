/*
  * Checks the MathML of the ASTnode 
  * is appropriate for the function being performed
  *
  * If an inconsistency is found, an error message is logged.
  */
void
PieceBooleanMathCheck::checkMath (const Model& m, const ASTNode& node, const SBase & sb)
{
  // does not apply in L3V2 for general consistency checking
  // BUT we want to use it for telling a converter that this occurs in L3V2
  if (this->mValidator.getCategory() == LIBSBML_CAT_MATHML_CONSISTENCY)
  {
    if (m.getLevel() == 3 && m.getVersion() > 1) return;
  }
  else
  {
    if (m.getLevel() != 3) return;
    else if (m.getVersion() == 1) return;
  }

  ASTNodeType_t type = node.getType();

  switch (type) 
  {
    case AST_FUNCTION_PIECEWISE:

      checkPiece(m, node, sb);
      break;


    case AST_FUNCTION:

      checkFunction(m, node, sb);
      break;

    default:

      checkChildren(m, node, sb);
      break;

  }
}