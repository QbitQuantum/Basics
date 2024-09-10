/*
 * Checks the MathML of the ASTnode 
 * is appropriate for the function being performed
 *
 * If an inconsistency is found, an error message is logged.
 */
void
NumericArgsMathCheck::checkMath (const Model& m, const ASTNode& node, const SBase & sb)
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
    case AST_PLUS:
    case AST_MINUS:
    case AST_TIMES:
    case AST_DIVIDE:
    case AST_POWER:
    case AST_FUNCTION_POWER:
    case AST_FUNCTION_ROOT:
    case AST_FUNCTION_ABS:
    case AST_FUNCTION_EXP:
    case AST_FUNCTION_LN:
    case AST_FUNCTION_LOG:
    case AST_FUNCTION_CEILING:
    case AST_FUNCTION_FLOOR:
    case AST_FUNCTION_FACTORIAL:
    case AST_FUNCTION_COS:
    case AST_FUNCTION_COT:
    case AST_FUNCTION_CSC:
    case AST_FUNCTION_SEC:
    case AST_FUNCTION_SIN:
    case AST_FUNCTION_TAN: 
    case AST_FUNCTION_COSH:
    case AST_FUNCTION_COTH:
    case AST_FUNCTION_CSCH:
    case AST_FUNCTION_SECH:
    case AST_FUNCTION_SINH:
    case AST_FUNCTION_TANH: 
    case AST_FUNCTION_ARCCOSH:
    case AST_FUNCTION_ARCCOTH:
    case AST_FUNCTION_ARCCSCH:
    case AST_FUNCTION_ARCSECH:
    case AST_FUNCTION_ARCSINH:
    case AST_FUNCTION_ARCTANH:
    case AST_FUNCTION_ARCCOS:
    case AST_FUNCTION_ARCCOT:
    case AST_FUNCTION_ARCCSC:
    case AST_FUNCTION_ARCSEC:
    case AST_FUNCTION_ARCSIN:
    case AST_FUNCTION_ARCTAN: 

      checkNumericArgs(m, node, sb);
      break;


    case AST_FUNCTION:

      checkFunction(m, node, sb);
      break;

    default:

      checkChildren(m, node, sb);
      break;

  }
}