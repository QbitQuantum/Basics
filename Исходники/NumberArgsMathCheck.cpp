/**
  * Checks the MathML of the ASTnode 
  * is appropriate for the function being performed
  *
  * If an inconsistency is found, an error message is logged.
  */
void
NumberArgsMathCheck::checkMath (const Model& m, const ASTNode& node, const SBase & sb)
{
  ASTNodeType_t type = node.getType();

  switch (type) 
  {
  case AST_FUNCTION_ABS:
  case AST_FUNCTION_ARCCOS:
  case AST_FUNCTION_ARCCOSH:
  case AST_FUNCTION_ARCCOT:
  case AST_FUNCTION_ARCCOTH:
  case AST_FUNCTION_ARCCSC:
  case AST_FUNCTION_ARCCSCH:
  case AST_FUNCTION_ARCSEC:
  case AST_FUNCTION_ARCSECH:
  case AST_FUNCTION_ARCSIN:
  case AST_FUNCTION_ARCSINH:
  case AST_FUNCTION_ARCTAN:
  case AST_FUNCTION_ARCTANH:
  case AST_FUNCTION_CEILING:
  case AST_FUNCTION_COS:
  case AST_FUNCTION_COSH:
  case AST_FUNCTION_COT:
  case AST_FUNCTION_COTH:
  case AST_FUNCTION_CSC:
  case AST_FUNCTION_CSCH:
  case AST_FUNCTION_EXP:
  case AST_FUNCTION_FACTORIAL:
  case AST_FUNCTION_FLOOR:
  case AST_FUNCTION_LN:
  case AST_FUNCTION_SEC:
  case AST_FUNCTION_SECH:
  case AST_FUNCTION_SIN:
  case AST_FUNCTION_SINH:
  case AST_FUNCTION_TAN:
  case AST_FUNCTION_TANH:
  case AST_LOGICAL_NOT:

    checkUnary(m, node, sb);
      break;

    case AST_DIVIDE:
    case AST_POWER:
    case AST_RELATIONAL_NEQ:
    case AST_FUNCTION_DELAY:
    case AST_FUNCTION_POWER:
    case AST_FUNCTION_LOG:       // a log ASTNode has a child for base

    checkBinary(m, node, sb);
      break;

    case AST_TIMES:
    case AST_PLUS:
    case AST_LOGICAL_AND:
    case AST_LOGICAL_OR:
    case AST_LOGICAL_XOR:
    case AST_RELATIONAL_EQ:
    case AST_RELATIONAL_GEQ:
    case AST_RELATIONAL_GT:
    case AST_RELATIONAL_LEQ:
    case AST_RELATIONAL_LT:
    case AST_FUNCTION_PIECEWISE:

     checkNary(m, node, sb);
      break;

    case AST_FUNCTION_ROOT:
    case AST_MINUS:
      
      checkSpecialCases(m, node, sb);
      break;

      
    case AST_FUNCTION:
      /* the case for a functionDefinition has its own rule
         from l2v4*/

      if (m.getLevel() < 3 && m.getVersion() < 4)
      {
        if (m.getFunctionDefinition(node.getName()) != NULL)
        {
          /* functiondefinition math */
          const ASTNode * fdMath = m.getFunctionDefinition(node.getName())->getMath();
          if (fdMath != NULL)
          {
          /* We have a definition for this function.  Does the defined number
	            of arguments equal the number used here? */

            if (node.getNumChildren() + 1 != fdMath->getNumChildren())
	          {
              logMathConflict(node, sb);
	          }
          }

        }
      }
      break;

    default:

      checkChildren(m, node, sb);
      break;

  }

}